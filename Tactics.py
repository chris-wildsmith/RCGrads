"""Function definitions for use by Main.py"""
import csv
import math

import TacticsCommon
import TacticsConfig
import MotorControl


def get_distance(a, b):
    """Return the distance between two Points."""
    delta_x = b.X - a.X
    delta_y = b.Y - a.Y
    return math.sqrt(delta_x * delta_x + delta_y * delta_y)


def try_parse_int(s, base=10, val=None):
    """Try parsing variable as int."""
    try:
        return int(s, base)
    except ValueError:
        return val  # Value to return if could not parse as int


def load_waypoints(waypoints_file):
    """Load all the Waypoints into a list of waypoint objects and return the list."""

    def validate_speed(speed, row_num):
        _speed = try_parse_int(speed)
        if _speed is not None:
            if _speed < 1 or _speed > 100:
                raise ValueError('While parsing waypoint file line ' +
                                 str(row_num) + ': Speed parameter is not in required range 1-100%!')
        else:
            raise ValueError('While parsing waypoint file line ' +
                             str(row_num) + ': Speed parameter is not an integer!')
        return _speed

    def validate_size(size, row_num):
        _size = try_parse_int(size)
        if _size is not None:
            if _size <= 0:
                raise ValueError('While parsing waypoint file line ' +
                                 str(row_num) + ': Size parameter cannot be < 0!')
        else:
            raise ValueError('While parsing waypoint file line ' +
                             str(row_num) + ': Size parameter is not an integer!')
        return _size

    # Create empty list to load waypoints into
    waypoint_list = []

    with open(waypoints_file, 'rb') as w_file:  # Open CSV file
        reader = csv.reader(w_file)  # Creates the reader
        row_number = 1
        for row in reader:  # Iterates the rows of the file
            # Ignore comments
            if row[0][0] == '#':
                row_number += 1
                continue
            # Read waypoint direction
            if row[2] == 'Forwards':
                direction = TacticsCommon.Direction.Fwd
            else:
                direction = TacticsCommon.Direction.Rvs
            # Read + validate waypoint speed
            validated_speed = validate_speed(row[3], row_number)
            # Read + validate waypoint size
            validated_size = validate_size(row[4], row_number)
            # If speed and size valid, add waypoint info to waypoint structure list
            new_waypoint = TacticsCommon.Waypoint(TacticsCommon.Point(int(row[0]), int(row[1])), direction,
                                                  validated_speed, validated_size)
            waypoint_list.append(new_waypoint)

            row_number += 1
    print 'Successfully loaded {0} waypoints from: {1}'.format(len(waypoint_list), waypoints_file)
    return waypoint_list


def calculate_delta_orientation(current_position, current_orientation, target_waypoint):
    """Calculate the required change in orientation."""
    calculated_orientation = 0.0

    # Get deltas in standard co-ordinate system
    delta_x = 1.0 * (target_waypoint.Position.X - current_position.X)
    delta_y = -1.0 * (target_waypoint.Position.Y - current_position.Y)

    # Handle 0-cases
    if delta_x == 0:
        if delta_y > 0:
            calculated_orientation = 0
        else:
            calculated_orientation = 180
    elif delta_y == 0:
        if delta_x > 0:
            calculated_orientation = 90
        else:
            calculated_orientation = -90
    else:
        # We can calculate the orientation
        calculated_orientation = math.atan2(delta_y, delta_x) * (180 / math.pi)
        calculated_orientation = 90 - calculated_orientation

    delta_orientation = calculated_orientation - current_orientation
    print "TACTICS>> Current Orientation:", current_orientation
    print "TACTICS>> Required Orientation:", calculated_orientation

    if target_waypoint.Direction == TacticsCommon.Direction.Rvs:
        delta_orientation += 180

    if delta_orientation > 180:
        delta_orientation = -1 * (360 - delta_orientation)
    elif delta_orientation < -180:
        delta_orientation += 360

    return delta_orientation


def at_waypoint(current_position, target_position, waypoint_size):
    """Determine if we're at a Waypoint."""
    # Waypoint is treated as a square, not circle - a waypoint's size is equivalent to half its width (its "radius")
    if target_position.X - waypoint_size < current_position.X < target_position.X + waypoint_size:
        if target_position.Y - waypoint_size < current_position.Y < target_position.Y + waypoint_size:
            return True
    return False


def get_position_and_orientation(message_pipe):
    """Determine position and orientation.
    Pass in pipe to image processor message process."""
    message_pipe.send(["request_position"])
    # Wait for position to be sent down pipe from message process
    while True:
        if message_pipe.poll():
            data = message_pipe.recv()
            if data[1].X != 0 and data[1].Y != 0:
                break
            message_pipe.send(["request_position"])
    return data[1], data[2]


def rotate_imu(delta_orientation, imu_pipe):
    """ Pass in: the delta orientation (+/-180deg format),
                 the IMU pipe """
    # Send a start message to the Imu Process
    print "TACTICS>> IMU" + str(delta_orientation)
    imu_pipe.send(["start_rotate", delta_orientation])

    # Rotate until delta orientation met
    while True:

        if imu_pipe.poll():
            data = imu_pipe.recv()

            # If Imu Process indicates success, stop rotate.
            if data[0] == "stop_rotate":
                MotorControl.stop()
                break

        # Rotate a small amount in the correct direction based on angle passed in
        if delta_orientation > 0:
            MotorControl.rotate(TacticsConfig.rotate_speed_slow, TacticsCommon.TurnDirection.Cw,
                                TacticsConfig.debug_mode)
        else:
            MotorControl.rotate(TacticsConfig.rotate_speed_slow, TacticsCommon.TurnDirection.Ccw,
                                TacticsConfig.debug_mode)


def rotate_overhead(initial_delta_orientation, target_waypoint, message_pipe):
    """ Pass in: the delta orientation (+/-180deg format),
                 the target waypoint
                 the message pipe """
    delta_orientation = initial_delta_orientation

    while True:
        # Rotate a small amount in the correct direction based on delta orientation
        if delta_orientation > 0:
            MotorControl.rotate(TacticsConfig.rotate_speed_slow, TacticsCommon.TurnDirection.Cw,
                                TacticsConfig.debug_mode)
        else:
            MotorControl.rotate(TacticsConfig.rotate_speed_slow, TacticsCommon.TurnDirection.Ccw,
                                TacticsConfig.debug_mode)

        # Get the latest position, blocks until position received
        current_position, current_orientation = get_position_and_orientation(message_pipe)

        # Calculate new delta
        delta_orientation = calculate_delta_orientation(current_position, current_orientation, target_waypoint)

        # If reached target orientation, stop rotate.
        if abs(delta_orientation) < TacticsConfig.rotate_tolerance_stop:
            MotorControl.stop()
            break


def drive(target_waypoint, current_position):
    """Drive in waypoint-specified direction at waypoint-specified speed or adaptive speed based on range
    to waypoint (if enabled in config)"""
    if TacticsConfig.enable_adaptive_speed:
        if get_distance(current_position, target_waypoint.Position) > TacticsConfig.start_slowdown_range:
            drive_speed = target_waypoint.Speed
        else:
            drive_speed = target_waypoint.Speed * TacticsConfig.slowdown_multiplier
    else:
        drive_speed = target_waypoint.Speed

    MotorControl.drive(drive_speed, target_waypoint.Direction, TacticsConfig.debug_mode)


def stop():
    """Stop motors."""
    MotorControl.stop(TacticsConfig.debug_mode)


def arm():
    """Arm motors/mbed."""
    MotorControl.arm(TacticsConfig.debug_mode)


def disarm():
    """Disarm motors/mbed."""
    MotorControl.disarm(TacticsConfig.debug_mode)
