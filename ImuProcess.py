""" The ImuProcess awaits a 'start' message from the control pipe.
    This message indicates a delta rotation which is measured by the IMU.
    Once this delta is achieved the process sends a 'stop' message."""
from multiprocessing import Process, Pipe
import smbus
import time
import datetime
import ImuControl
import sys
import TacticsConfig

dT = 0.02  # 20ms
threshold = TacticsConfig.rotate_tolerance_stop


def imu_process(control_pipe):
    """Main process handling IMU."""
    bus = ImuControl.init_imu()

    while True:
        # Wait for a 'start'
        if control_pipe.poll(None):  # None signifies blocking
            payload = control_pipe.recv()
            if payload[0] == "start_rotate":
                # Start calculating delta
                calculate_delta(bus, payload[1])
                control_pipe.send(["stop_rotate"])
            if payload[0] == "get_heading":
                # Return magnetometer readings
                raw_heading = ImuControl.get_raw_heading(bus)
                compensated_heading = ImuControl.get_tilt_compensated_heading(bus)
                control_pipe.send([raw_heading, compensated_heading])
            elif payload[0] == "quit":
                break


def calculate_delta(bus, delta):
    """Blocking function that returns once the delta has been obtained."""
    # Init gyro deltas
    gyro_x_delta = 0
    gyro_y_delta = 0
    gyro_z_delta = 0

    # TODO: Perhaps add a timer that kills the rotate after X time
    while True:
        start_time = datetime.datetime.now()

        gyro_data = ImuControl.get_gyro_readings(bus)

        rate_gyr_x = gyro_data[0]
        rate_gyr_y = gyro_data[1]
        rate_gyr_z = gyro_data[2]

        gyro_x_delta += rate_gyr_x * dT
        gyro_y_delta += rate_gyr_y * dT
        gyro_z_delta += rate_gyr_z * dT

        # print abs(gyro_z_delta)
        if abs(gyro_z_delta) > (abs(delta) - threshold):
            break

        while (datetime.datetime.now() - start_time).total_seconds() < dT:
            time.sleep(0.0001)


if __name__ == '__main__':
    im_Main, im_Imu = Pipe()
    process = Process(target=imu_process, args=(im_Imu,))
    process.start()

    print "Start Rotation"
    im_Main.send(["start_rotate", 90])

    stop = False
    while not stop:
        # Send rotation request to mBed
        if im_Main.poll():
            data = im_Main.recv()
            if data[0] == "stop_rotate":
                print "Stop Rotation"
                # Send stop to mBed
                stop = True

    im_Main.send(["quit"])
    process.join()
    time.sleep(1)
    im_Main.close()
    im_Imu.close()
    process.terminate()
    sys.exit()
