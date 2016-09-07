"""Config values for RC code."""

# Configuration

# <<-- START GENERAL CONFIG -->>
debug_mode = False
use_imu = True                   # Enable or disable use of IMU.  If disabled, all orientation calculations will be done
                                # by ImageProcessor.
map_scaling_factor = 2          # The map scaling factor - currently not used in code as waypoint generator program
                                # scales up drawn waypoints itself
# <<-- END GENERAL CONFIG -->>


# <<-- START CHARIOT DYNAMICS CONFIG -->>
drive_time = 0.3                # Time chariot will drive straight for in seconds (blocking)
rotate_time = 0.1               # Time chariot will rotate for in seconds (blocking)

rotate_speed_slow = 55          # Slow Rotate.
rotate_speed_fast = 65          # Fast Rotate - currently not used in code.

rotate_tolerance_start = 5      # The smallest orientation error to target waypoint required to start a rotate
rotate_tolerance_stop = 10      # Stop rotation when orientation to target waypoint is below this threshold
rotate_tolerance_slow = 50      # Slow rotation under this tolerance

overshoot_delta = 150          # The distance over which the chariot will be deemed to have overshot a waypoint.
# <<-- END CHARIOT DYNAMICS CONFIG -->>


# <<-- START ADAPTIVE SPEED CONFIG -->>
enable_adaptive_speed = True    # Enable or disable adaptive speed
slowdown_multiplier = 0.50      # The fraction of the waypoint speed to use when we approach a waypoint
start_slowdown_range = 100      # Range (px) from waypoint boundary at which adaptive slow down will start
# << --END ADAPTIVE SPEED CONFIG -->>
