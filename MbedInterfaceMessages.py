__author__ = 'Glenn Startin'
# Basic classes to contain Mbed Interface Data, in and out messages

import binascii
import MbedInterfaceCommon

class MbedInterfaceMsg:
    "Base Class for TP and Mbed messages"
    def __init__(self, msgID, payloadLength, initialPayload, outMsg):
        self.msgID = msgID
        self.payloadLength = bytearray([0, payloadLength]) # This covers the 2 byte payload length with the first byte hardcoded to zero, there are currently no messages with payload lengths larger than 255
        self.header = bytearray([0xFF, msgID]) + self.payloadLength
        self.footer = bytearray([0x0A])
        if initialPayload is not None:
            self.payload = bytearray(initialPayload)
            self.rawMessage = self.header + self.payload + self.footer
        else:
            self.payload = None
            self.rawMessage = self.header + self.footer
            self.outMsg = outMsg

    def update_payload(self, payload):

        if len(payload) == self.payloadLength[1]:
            self.payload = payload
            self.rawMessage = self.header + self.payload + self.footer
        else:
            print 'ERROR: Attempted payload update failed for Message ID', self.msgID, '! Length of new payload length did not match required payload length for this message ID.'

class TPReadyMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload=None):
        MbedInterfaceMsg.__init__(self, 0, 0, initialPayload, True)  # initialPayload should be None

class MbedReadyMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload=None):
        MbedInterfaceMsg.__init__(self, 1, 0, initialPayload, False)  # initialPayload should be None

class MotionReqMsg(MbedInterfaceMsg):
    def __init__(self, motionDir=MbedInterfaceCommon.Motion.Stop, speed=0):
        initialPayload = bytearray([motionDir, speed])
        MbedInterfaceMsg.__init__(self, 2, 2, initialPayload, True)
    # Do we need some protection measure to stop immediate motion switching?
    # I dont wanna blow a mosfet! LOL blow

    def setMotion(self, motionDir=MbedInterfaceCommon.Motion.Stop, speed=0):
        if motionDir is not None and speed is not None:
            self.payload = bytearray([motionDir, speed])
            self.update_payload(self.payload)
        elif speed>100:
            self.payload = bytearray([motionDir, 100])
        # else should be some sort of exception or throw... need more time to learn though

class MotionAckMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload=None):
        MbedInterfaceMsg.__init__(self, 3, 0, initialPayload, False)  # initialPayload should be None


class RangerReadingReqMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload=None):
        MbedInterfaceMsg.__init__(self, 4, 0, initialPayload, True)  # initialPayload should be None


class RangerReadingResultsMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload):
        MbedInterfaceMsg.__init__(self, 5, 12, initialPayload, False)

class EmergencyStopReqMsg(MbedInterfaceMsg):
    def __init__(self, initialPayload=None):
        MbedInterfaceMsg.__init__(self, 6, 0, initialPayload, True)  # initialPayload should be None

# Function to print message contents out as hex
def print_message(message):
    #print message.encode('string_escape')
    print binascii.hexlify(message)


# This if block won't run when file is imported. Bug Checking.
if __name__ == "__main__":
    print("Running MbedInterfaceMessages as Main \n")
    print("Stop enum value = " + str(MbedInterfaceCommon.Motion.Stop))
    tpReadyMsg = TPReadyMsg()
    motionMsg = MotionReqMsg()
    print("TPReadyMsg ID is " + str(tpReadyMsg.msgID))
    motionMsg.setMotion(MbedInterfaceCommon.Motion.Forward, 60)
    print("Set motion params - Dir:=" + str(motionMsg.payload[0]) + " - Speed:=" + str(motionMsg.payload[1]))
    motionMsg.setMotion(MbedInterfaceCommon.Motion.Backward, 40)
    print("Set motion params - Dir:=" + str(motionMsg.payload[0]) + " - Speed:=" + str(motionMsg.payload[1]))
