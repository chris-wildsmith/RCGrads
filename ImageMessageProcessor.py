
class ImageProcMessage(object):
    def __init__(self):
        self.ChariotCoordX = 0
        self.ChariotCoordY = 0
        self.ChariotOrientation = 0
        self.Valid = 0
        self.FootballCoordX = 0
        self.FootballCoordY = 0
        
    def decodeImageProcMessage(self, packetPayload):
        if len(packetPayload) == 20:
            print "Packet before decode: ", packetPayload
            self.ChariotCoordX = int(packetPayload[0:4])
            self.ChariotCoordY = int(packetPayload[4:8])
            self.ChariotOrientation = int(packetPayload[8:11])
            self.Valid = int(packetPayload[11:12])
            self.FootballCoordX = int(packetPayload[12:16])
            self.FootballCoordY = int(packetPayload[16:20])
        
        
if __name__ == "__main__":
    IPM = ImageProcMessage()
    IPM.decodeImageProcMessage("19201080135011110000")
    print str(IPM.ChariotCoordX)  
    print str(IPM.ChariotCoordY) 
    print str(IPM.Valid)
    print str(IPM.FootballCoordX)
    print str(IPM.FootballCoordY)