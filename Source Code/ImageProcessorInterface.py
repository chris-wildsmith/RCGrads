import NetworkComms
import ImageMessageProcessor


class ImageProcessorInterface:
    """IP class to store original obstacle map and buffer for coordinates 
    and orientation received from image processing"""
    def __init__(self):
        self.wifiInterface = NetworkComms.NetworkComms('wlan0')#what is this interface
        self.decodedPacket = ImageMessageProcessor.ImageProcMessage()
        self.currentOrientation = 0
        self.currentX = 0
        self.currentY = 0
        
    #def startUpSequence(self):
        #Probably require numpy library       
        
        #if this was done with hex strings and there was no crossover between bytes its much simpler
        
    def receiveMessage(self):
        packetLoad = self.wifiInterface.receivePacket()
        self.decodedPacket.decodeImageProcMessage(packetLoad)

    def getChariotX(self):
        return self.decodedPacket.ChariotCoordX

    def getChariotY(self):
        return self.decodedPacket.ChariotCoordY

    def getOrientationFromCam(self):
        return self.decodedPacket.ChariotOrientation

    def getDataValid(self):
        if self.decodedPacket.Valid == 1:
            return True
        else:
            return False

    def getFootballX(self):
        return self.decodedPacket.FootballCoordX

    def getFootballY(self):
        return self.decodedPacket.FootballCoordY
    """ Methods no longer required due to reduced information

    def getBarrelX(self):
        return self.decodedPacket.iBarrelCoordX

    def getBarrelY(self):
        return self.decodedPacket.iBarrelCoordY

    def getBarrelPostX(self):
        return self.decodedPacket.iBarrelPostCoordX

    def getBarrelPostY(self):
        return self.decodedPacket.iBarrelPostCoordY

    def getGoalX(self):
        return self.decodedPacket.iGoalX

    def getGoalY(self):
        return self.decodedPacket.iGoalY

    def getPaddleX(self):
        return self.decodedPacket.iPaddleCoordX

    def getPaddleY(self):
        return self.decodedPacket.iPaddleCoordY

    def getRampX(self):
        return self.decodedPacket.iRampCoordX

    def getRampY(self):
        return self.decodedPacket.iRampCoordY
        """

# GS Code
#binCoords = buffer >> 10 #bitshift right 10 to get just the coordinate values thats 9 for the orientation plus 1 to meet the byte edge of 32 bits.
#binOrient = buffer & 111111111 # mask out the 22 coordinate bits
#binOrient = binOrient >> 1 #Then right shit one to meet byte edge.
#self.currentOrientation = int(binOrient, 2) # convert binary string to integer
#binX = binCoords >> 11 #masking out the y coordinates
#binY = binCoords & 11111111111 #masking out the x coordinates
#self.currentX = int(binX, 2)
#self.currentY = int(binY, 2)
#Fuck knows if this will work