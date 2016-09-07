""" Manually read Gyro and Accelerometer data from IMU. """
import smbus
import math

REG_WHO_AM_I = 0x0F
REG_CTRL_1 = 0x20
REG_CTRL_2 = 0x21
REG_CTRL_4 = 0x23
REG_CTRL_5 = 0x24
REG_CTRL_6 = 0x25
REG_CTRL_7 = 0x26

GYRO_ADDRESS = 0x6B
GYRO_SENSITIVITY = 0.07  # 70 mdps/digit
GYRO_REG_OUT_X_L = 0x28

ACC_ADDRESS = 0x1D
ACC_SENSITIVITY = 0.244  # 0.244 mg/LSB
ACC_REG_OUT_X_L_A = 0x28

MAG_ADDRESS = 0x1D
MAG_REG_OUT_X_L = 0x08


def get_int16(h_byte, l_byte):
    """Creates an int16 from a high byte and low byte."""
    raw_value = h_byte << 8 | l_byte

    if h_byte & 0x80 == 0x80:
        raw_value -= (1 << 16)
    return raw_value


def get_mag_readings(bus):
    """Returns the raw magnetometer readings from the IMU."""
    block_data = bus.read_i2c_block_data(MAG_ADDRESS, MAG_REG_OUT_X_L | 0x80, 6)

    mag_raw_x = get_int16(block_data[1], block_data[0])
    mag_raw_y = get_int16(block_data[3], block_data[2])
    mag_raw_z = get_int16(block_data[5], block_data[4])

    return mag_raw_x, mag_raw_y, mag_raw_z


def get_raw_heading(bus):
    """Returns the raw heading from the magnetometer readings."""
    mag_x, mag_y, mag_z = get_mag_readings(bus)

    heading = 180 * math.atan2(mag_y, mag_x) / math.pi
    return heading


def get_tilt_compensated_heading(bus):
    """Returns a tilt-compensated heading from the magnetometer readings."""
    # Magnetometer
    mag_x, mag_y, mag_z = get_mag_readings(bus)

    # Accelerometer
    acc_x, acc_y, acc_z = get_acc_readings(bus)

    acc_x_norm = acc_x / math.sqrt(acc_x * acc_x + acc_y * acc_y + acc_z * acc_z)
    acc_y_norm = acc_y / math.sqrt(acc_x * acc_x + acc_y * acc_y + acc_z * acc_z)

    pitch = math.asin(acc_x_norm)
    roll = - math.asin(acc_y_norm / math.cos(pitch))

    mag_x_comp = mag_x * math.cos(pitch) + mag_z * math.sin(pitch)
    mag_y_comp = mag_x * math.sin(roll) * math.sin(pitch) + mag_y * math.cos(roll) - mag_z * math.sin(roll) * math.cos(
        pitch)

    heading = 180.0 * math.atan2(mag_y_comp, mag_x_comp) / math.pi

    return heading


def get_gyro_readings(bus):
    """Returns the raw gyro readings from the IMU."""
    block_data = bus.read_i2c_block_data(GYRO_ADDRESS, GYRO_REG_OUT_X_L | 0x80, 6)

    gyr_raw_x = get_int16(block_data[1], block_data[0])
    gyr_raw_y = get_int16(block_data[3], block_data[2])
    gyr_raw_z = get_int16(block_data[5], block_data[4])

    rate_gyr_x = float(gyr_raw_x) * GYRO_SENSITIVITY
    rate_gyr_y = float(gyr_raw_y) * GYRO_SENSITIVITY
    rate_gyr_z = float(gyr_raw_z) * GYRO_SENSITIVITY

    return rate_gyr_x, rate_gyr_y, rate_gyr_z


def get_acc_readings(bus):
    """Returns the raw accelerometer readings from the IMU."""
    block_data = bus.read_i2c_block_data(ACC_ADDRESS, ACC_REG_OUT_X_L_A | 0x80, 6)

    acc_raw_x = get_int16(block_data[1], block_data[0])
    acc_raw_y = get_int16(block_data[3], block_data[2])
    acc_raw_z = get_int16(block_data[5], block_data[4])

    acc_x = float(acc_raw_x) * ACC_SENSITIVITY
    acc_y = float(acc_raw_y) * ACC_SENSITIVITY
    acc_z = float(acc_raw_z) * ACC_SENSITIVITY

    return acc_x, acc_y, acc_z


def init_imu():
    """Performs IMU initalisation."""
    bus = smbus.SMBus(1)

    print "Enabling Gyro..."
    bus.write_byte_data(GYRO_ADDRESS, REG_CTRL_1, 0b00001111)  # Normal power mode, all axes enabled
    bus.write_byte_data(GYRO_ADDRESS, REG_CTRL_4, 0b00110000)  # Continuous, 2000dps

    print "Enabling Acc..."
    bus.write_byte_data(ACC_ADDRESS, REG_CTRL_1, 0b01100111)  # X,Y,Z enabled, 100Hz data rate
    bus.write_byte_data(ACC_ADDRESS, REG_CTRL_2, 0b00100000)  # +/- 16G full scale

    print "Enabling Mag..."
    bus.write_byte_data(MAG_ADDRESS, REG_CTRL_5, 0b11110000)  # High res, 50Hz data rate
    bus.write_byte_data(MAG_ADDRESS, REG_CTRL_6, 0b01100000)  # +- 12 gauss
    bus.write_byte_data(MAG_ADDRESS, REG_CTRL_7, 0b00000000)  # Continuous conversion

    return bus
