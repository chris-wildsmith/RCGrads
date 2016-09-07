__author__ = 'Glenn Startin'

# import OutwardNetworkComms
# import InboundNetworkComms
import MbedInterfaceCommon
import MbedInterfaceMessages
import NetworkComms
    
class MbedInterface:
    def __init__ (self): 
        # initialise all messages ready to send/receive data
        self.tpReadyMsg = MbedInterfaceMessages.TPReadyMsg()
        self.mbedReadyMsg = MbedInterfaceMessages.MbedReadyMsg()
        self.motionRequestMsg = MbedInterfaceMessages.MotionReqMsg(MbedInterfaceCommon.Motion.Stop, 0)
        self.motionAckMsg = MbedInterfaceMessages.MotionAckMsg()
        self.rangeReqMsg = MbedInterfaceMessages.RangerReadingReqMsg()
        self.rangerResultsMsg = MbedInterfaceMessages.RangerReadingResultsMsg([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
        self.EmergencyStopMsg = MbedInterfaceMessages.EmergencyStopReqMsg()
        self.mbedReady = False
        self.ethernetInterface = NetworkComms.NetworkComms('eth0')

    def processPacket(self, packet):
        """Puts a single packet into the bytes buffer,
        then processes this by stripping it into a base message and payload.
        Finally handles the relevant message and puts it into that message type
        member variable"""

        if packet: #If packet is not empty i.e. sniff did not time out and packet was received from mbed
            if packet[0] == "\xFF": #If valid start byte

                #Find end of message marker
                end_message = packet.find("\x0A")

                if end_message > 3: #If message contains at least 4 bytes i.e. valid header

                    msgID = ord(packet[1]) # Get message ID. ord converts from unicode string char to int

                    #Check message IDs for valid ones
                    if msgID == self.motionAckMsg.msgID:
                        if self.CheckMsgLength(end_message, self.motionAckMsg.payloadLength[1]):
                            print 'STATUS: Motion Ack message received from mbed.'
                            return True
                        else:
                            print 'ERROR: Motion Ack message received with invalid payload length!'
                            return False

                    elif msgID == self.rangerResultsMsg.msgID: #If ranger results message ID and has non-zero payload
                        if self.CheckMsgLength(end_message, self.rangerResultsMsg.payloadLength[1]):
                            payload = bytearray(packet[4:end_message])
                            self.rangerResultsMsg.update_payload(payload)
                            print 'STATUS: Ranger Results message received from mbed.'
                            return True
                        else:
                            print 'ERROR: Ranger Results message received with invalid payload length!'
                            return False

                    elif msgID == self.mbedReadyMsg.msgID:
                        if self.CheckMsgLength(end_message, self.mbedReadyMsg.payloadLength[1]):
                            print 'STATUS: Mbed Ready message received from mbed.'
                            self.mbedReady = True
                            return True
                        else:
                            print 'ERROR: Mbed Ready message received with invalid payload length!'
                            return False
                    else:
                        print 'ERROR: Invalid message ID or payload size received from mbed!'
                        return False
                else:
                    print 'ERROR: Malformed packet format received from mbed!'
                    return False
            else:
                print 'WARNING: Unrecognised packet format received from mbed MAC address!'
                return False
        else:
            return False

    def TPReady(self):
        # Send TPReadyMessage
        self.ethernetInterface.sendPacket(self.tpReadyMsg.rawMessage.__str__())
    
    def isMbedReady(self):
        return self.mbedReady
        
    def Initialise(self):
        print 'STATUS: Sending TP Ready message to mbed...'
        self.TPReady()
        #Receive and process packet from interface with 2 second timeout
        self.processPacket(self.ethernetInterface.receivePacket(2))
        return self.isMbedReady()
            
    def MotionReq(self, dir, speed):
        #Send motionRequestMsg
        #Use dir parameter from TacticsCommon.Direction
        _dir = self.ValidateDirection(dir)
        _speed = self.ValidateSpeed(speed)
        self.motionRequestMsg.setMotion(_dir, _speed)
        self.ethernetInterface.sendPacket(self.motionRequestMsg.rawMessage.__str__())
    
    def RangerReq(self):
        #Send RangerReadingReqMsg
        self.ethernetInterface.sendPacket(self.rangeReqMsg.rawMessage.__str__())

    def EmergencyStopReq(self):
        #Send EmergencyStopMsg
        self.ethernetInterface.sendPacket(self.EmergencyStopMsg.rawMessage.__str__())

    #Helper functions
    def CheckMsgLength(self, end_message, length):
        if (end_message - 4) == length:
            return True
        else:
            return False

    def ValidateSpeed(self, speed):
        _speed = self.TryParseInt(speed)
        if(_speed is not None):
            if(speed < 0 or speed > 100):
                raise ValueError('Speed parameter passed in is not in required range 0-100%!')
        else:
            raise ValueError('Speed parameter passed in is not an integer!')
        return _speed

    def ValidateDirection(self, dir):
        _dir = self.TryParseInt(dir)
        if(_dir is not None):
            if(dir < 0 or dir > 4):
                raise ValueError('Direction parameter passed in is not in required range 0-4!')
        else:
            raise ValueError('Direction parameter passed in is not an integer!')
        return _dir

    def TryParseInt(self, s, val=None):
      try:
        return int(s)
      except ValueError:
        return val #Value to return if could not parse as int

    def Test(self):
        #Test sending of all TP messages
        self.TPReady()
        self.MotionReq(MbedInterfaceCommon.Motion.Stop,0)
        self.MotionReq(MbedInterfaceCommon.Motion.Forward,20)
        self.MotionReq(MbedInterfaceCommon.Motion.Backward,40)
        self.MotionReq(MbedInterfaceCommon.Motion.AntiClockwise,80)
        self.MotionReq(MbedInterfaceCommon.Motion.Clockwise,100)
        #Sending RangerReq blocks receiving of other messages at mbed until ranging complete
        self.RangerReq()


if __name__ == "__main__":
    IMbed = MbedInterface()
    IMbed.Initialise()
    IMbed.Test()
