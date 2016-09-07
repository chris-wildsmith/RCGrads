"""Motor control library."""
import MbedInterface
import MbedInterfaceCommon
import TacticsCommon
import time
import TacticsConfig

IMbed = MbedInterface.MbedInterface()


# Functions
# =========

def rotate(speed, direction, debug=False):
    """Rotate the chariot a small amount in the direction specified."""
    if not debug:
        if direction == TacticsCommon.TurnDirection.Cw:
            # print "MOTORCONTROL>> Rotate CW at "  + str(speed) + "% speed"
            IMbed.MotionReq(MbedInterfaceCommon.Motion.Clockwise, speed)
        else:
            # print "MOTORCONTROL>> Rotate CCW at"  + str(speed) + "% speed"
            IMbed.MotionReq(MbedInterfaceCommon.Motion.AntiClockwise, speed)
        time.sleep(TacticsConfig.rotate_time)
        # Stop()
    return 0


def drive(speed, direction, debug=False):
    """Drive the chariot a small amount in the direction specified."""
    if not debug:
        if direction == TacticsCommon.Direction.Fwd:
            print "MOTORCONTROL>> Drive Fwd at " + str(speed) + "% speed"
            IMbed.MotionReq(MbedInterfaceCommon.Motion.Forward, speed)
        else:
            print "MOTORCONTROL>> Drive Rvs at " + str(speed) + "% speed"
            IMbed.MotionReq(MbedInterfaceCommon.Motion.Backward, speed)
        time.sleep(TacticsConfig.drive_time)
        stop()
    return 0


def stop(debug=False):
    """Stop the chariot."""
    if not debug:
        print "MOTORCONTROL>> Stop"
        IMbed.MotionReq(MbedInterfaceCommon.Motion.Stop, 0)
    return 0


def arm(debug=False):
    """Arm the chariot."""
    if not debug:
        print "MOTORCONTROL>> Waiting for mbed to confirm initialisation..."
        while not IMbed.Initialise():  # Keep looping every second until mbed initialised
            time.sleep(0.1)
            print "MOTORCONTROL>> WARNING: Mbed not yet ready...Retrying mbed initialisation!"
        print "MOTORCONTROL>> Mbed interface successfully initialised!"
        print "MOTORCONTROL>> Armed!"
    return 0


def disarm(debug=False):
    # Disarm the chariot
    if not debug:
        IMbed.EmergencyStopReq()
        print "MOTORCONTROL>> Disarmed!"
    return 0
