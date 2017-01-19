__author__ = 'christopherwildsmith'

from scapy.all import *

class NetworkComms:
    def __init__(self, interface):
        # Create and initialise an ethernet packet for use by the class
        # Note: ethernet packets are used by both the ethernet and wifi
        self.packet = Ether()/IP()
        self.packet.src = "00:11:22:33:44:55"
        self.packet.dst = "FF:FF:FF:FF:FF:FF"
        self.packet.type = 0x0600
        self.data = ""
        self.interface = interface

        #Define MAC address of mbed for use by sniff filter
        #Dangerous if we swap mbed!
        self.mbed_src = "00:02:f7:f2:09:54"

    def sendPacket(self, data):
        # Update the packet data before sending it out on the relevant interface
        # The interface is either 'eth0' or 'wlan0'
        self.data = data
        # for element in data:
        #    print element
        # Concatinate the packet header with the data
        completePacket = self.packet/self.data
        # List the packet details on the console
        #ls(completePacket)
         # Send the packet
        sendp(completePacket, iface= self.interface, verbose=0)

    def receivePacket(self, timeout=2):
        #Sniff a single mbed source packet

        #packet = sniff(iface=self.interface, prn=lambda x: x.show(), count=1, timeout=timeout, lfilter=lambda d: d.src == self.mbed_src )
        if self.interface == "eth0":
            packet = sniff(iface=self.interface, count=1, timeout=timeout, lfilter=lambda d: d.src == self.mbed_src )
            if packet: #If packet is not empty i.e. message received from mbed
                packetLoad = packet[0].load
                return packetLoad
            else:
                return False #Return false if sniff timed out and returned empty packet
        elif self.interface == "wlan0":
            bValidPacket = False
            while not bValidPacket:
                try:
                    packet = sniff(iface=self.interface, count=1, filter="udp port 9090")
                    packetLoad = packet[0].load
                    bValidPacket = True
                except AttributeError:
                    print "Invalid Wifi Packet Received"
                    bValidPacket = False
            return packetLoad
