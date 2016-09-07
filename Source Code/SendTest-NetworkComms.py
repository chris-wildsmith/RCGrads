__author__ = 'christopherwildsmith'

from scapy.all import *

class NetworkComms:
    def __init__(self, interface):
        # Create and initialise an ethernet packet for use by the class
        # Note: ethernet packets are used by both the ethernet and wifi
        
        self.packet = Ether()
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
        ls(completePacket)
        # Send the packet
        sendp(completePacket, iface= self.interface, verbose=0)

if __name__ == "__main__":
    while True:
        test = NetworkComms("eth0")
        test.sendPacket("hello")
        print "Sent Packet"

"""
from scapy.all import *
from socket import *

def sendPacket(src, dst, eth_type, payload, interface = "eth0"):
    Send raw Ethernet packet on interface.
    assert(len(src) == len(dst) == 6) # 48-bit ethernet addresses
    assert(len(eth_type) == 2) # 16-bit ethernet type

    s = socket(AF_PACKET, SOCK_RAW)
    # From the docs: "For raw packet
    # sockets the address is a tuple (ifname, proto [,pkttype [,hatype]])"
    s.bind((interface, 0))
    s.send(src + dst + eth_type + payload)

if __name__ == "__main__":
    while True:
        sendPacket("\x00\x11\x22\x33\x44\x55", "\xFF\xFF\xFF\xFF\xFF\xFF", "\x06\x00", "hello")
        print "Sent Packet"
        """
