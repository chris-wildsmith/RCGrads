""" Main file for Rampaging Chariots automated challenge."""
import sys
import time
from multiprocessing import Process, Pipe
import copy
import TacticsCommon
import TacticsConfig
import Tactics
import MsgProcess

if TacticsConfig.use_imu:
    import ImuProcess

# Main
# ====

# Orientation & Position
delta_orientation = 0
last_delta_orientation = 0

# Start processes & pipes
print "MAIN>> Starting processes..."
# Pipes - (procA)(procB)_PipeEnd
tm_Tactics, tm_Msg = Pipe()
ti_Tactics, ti_Imu = Pipe()

# Processes
msg_process = Process(target=MsgProcess.msg_process, args=(tm_Msg,))
msg_process.start()

if TacticsConfig.use_imu:
    imu_process = Process(target=ImuProcess.imu_process, args=(ti_Imu,))
    imu_process.start()

# Load the Waypoints
print "MAIN>> Loading waypoints..."
waypoints_file = "waypoints.waypoint"
waypoint_list = Tactics.load_waypoints(waypoints_file)
target_waypoint_index = 0
target_waypoint = waypoint_list[target_waypoint_index]
print "MAIN>> Loaded waypoints: " + str(waypoint_list)

# Initialise and arm mbed prior to start of main loop
Tactics.arm()

print "MAIN>> Starting..."
# Main
while True:
    try:
        # Do main computation here: 

        # Get chariot position
        current_position, current_orientation = Tactics.get_position_and_orientation(tm_Tactics)

        # Check if we're at the next waypoint
        print 'MAIN>> Heading for waypoint {0} of {1}: {2}'.format(target_waypoint_index + 1, len(waypoint_list),
                                                                   target_waypoint.Position)

        if Tactics.at_waypoint(current_position, target_waypoint.Position, target_waypoint.Size):
            print 'MAIN>> At waypoint {0} {1}'.format(target_waypoint_index + 1, target_waypoint.Position)
            waypoint_list[target_waypoint_index].Traversed = True

            if target_waypoint_index == len(waypoint_list) - 1:
                print "MAIN>> Finished!"
                break
            else:
                # Update the target waypoint
                target_waypoint_index += 1
                target_waypoint = waypoint_list[target_waypoint_index]
                # TODO: Is this stop necessary?
                Tactics.stop()
                print 'MAIN>> On to waypoint {0} of {1}: {2}'.format(target_waypoint_index + 1, len(waypoint_list),
                                                                     target_waypoint.Position)

        # Calculate required orientation
        last_delta_orientation = delta_orientation
        delta_orientation = Tactics.calculate_delta_orientation(current_position, current_orientation, target_waypoint)

        # Get the distance to the next waypoint
        waypoint_dist = Tactics.get_distance(current_position, target_waypoint.Position)
        deltaDiff = abs(delta_orientation - last_delta_orientation)

        if waypoint_dist < TacticsConfig.start_slowdown_range and deltaDiff > TacticsConfig.overshoot_delta:
            tempWaypoint = copy.deepcopy(target_waypoint)
            if tempWaypoint.Direction == TacticsCommon.Direction.Fwd:
                tempWaypoint.Direction = TacticsCommon.Direction.Rvs
            else:
                tempWaypoint.Direction = TacticsCommon.Direction.Fwd
            Tactics.drive(tempWaypoint, current_position)
        else:

            # Determine whether the orientation delta justifies rotating.
            if abs(delta_orientation) >= TacticsConfig.rotate_tolerance_start:
                if TacticsConfig.use_imu:
                    Tactics.rotate_imu(delta_orientation, ti_Tactics)
                else:
                    Tactics.rotate_overhead(delta_orientation, target_waypoint, tm_Tactics)

            # Drive a small amount in waypoint specified direction with speed specified by waypoint or adaptive speed
            # as per TacticsConfig
            Tactics.drive(target_waypoint, current_position)

    except KeyboardInterrupt:
        break

# Stop and disarm motors
Tactics.stop()
Tactics.disarm()

# Wait for main process to exit
print "MAIN>> Killing processes..."
tm_Tactics.send(['quit'])
ti_Tactics.send(['quit'])
msg_process.join()

if TacticsConfig.use_imu:
    imu_process.join()

# Allow processes to finish-up and terminate
time.sleep(1)
tm_Tactics.close()
tm_Msg.close()
ti_Tactics.close()
ti_Imu.close()

msg_process.terminate()
if TacticsConfig.use_imu:
    imu_process.terminate()

print "MAIN>> Shutdown complete."
sys.exit()
