"""Message processing library."""
from multiprocessing import Process, Pipe
import ImageProcessorInterface
import TacticsCommon
import time
import sys


def msg_process(tactics_pipe):
    """Message processing process."""
    # Create the ImageProcessorInterface
    iip = ImageProcessorInterface.ImageProcessorInterface()

    while True:
        if tactics_pipe.poll():  # Non-blocking
            data = tactics_pipe.recv()
            msg_name = data[0]
            print msg_name  # Request name

            # Service request
            if msg_name == 'quit':
                break
            elif msg_name == 'request_position':
                iip.receiveMessage()
                position = TacticsCommon.Point(iip.getChariotX(), iip.getChariotY())
                orientation = iip.getOrientationFromCam()

                # Send position and orientation
                tactics_pipe.send(["position", position, orientation])
                # TODO: Continually read data to ensure up to date information.
                # else
                #
                #    iip.receiveMessage()
                #    # Timestamp data?


if __name__ == '__main__':
    mm_Main, mm_Msg = Pipe()
    process = Process(target=msg_process, args=(mm_Msg,))
    process.start()

    mm_Main.send(["quit"])
    process.join()
    time.sleep(1)
    mm_Main.close()
    mm_Msg.close()
    process.terminate()
    sys.exit()
