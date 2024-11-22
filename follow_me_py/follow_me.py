import lcm
import time
import numpy as np
from mbot_lcm_msgs import lidar_t, twist2D_t


# Get distance to wall
def find_fwd_dist(ranges, thetas, window=5):
    """Find the distance to the nearest object in front of the robot.

    Args:
        ranges (list): The ranges from the Lidar scan.
        thetas (list): The angles from the Lidar scan.
        window (int, optional): The window to average ranges over. Defaults to 5.

    Returns:
        float: The distance to the nearest obstacle in front of the robot.
    """
    if len(ranges) < window or len(thetas) < 0:
        return -1
    # Grab the rays near the front of the scan.
    fwd_ranges = np.array(ranges[:window] + ranges[-window:])
    fwd_thetas = np.array(thetas[:window] + thetas[-window:])
    # Grab just the positive values.
    valid_idx = (fwd_ranges > 0).nonzero()
    fwd_ranges, fwd_thetas = fwd_ranges[valid_idx], fwd_thetas[valid_idx]

    # Compute forward distances.
    fwd_dists = fwd_ranges * np.cos(fwd_thetas)
    return np.mean(fwd_dists)  # Return the mean.


def handleLidar(channel, msg):
    # When we get a message, decode the data and print it out.
    msg = lidar_t.decode(msg)

    dist_to_wall = find_fwd_dist(msg.ranges, msg.thetas)

    # TODO: Write your follow me controller here.


if __name__ == '__main__':
    lcm_handler = lcm.LCM("udpm://239.255.76.67:7667?ttl=1")

    # Subscribe to the lidar channel.
    lcm_handler.subscribe("LIDAR", handleLidar)

    # Listen for messages forever.
    try:
        while True:
            lcm_handler.handle_timeout(500)
    except Exception as e:
        print(e)
    finally:
        # Stop the robot before exiting.
        print("Stopping the robot!")
        cmd = twist2D_t()
        cmd.vx, cmd.vy, cmd.wz = 0, 0, 0
        lcm_handler.publish("MBOT_VEL_CMD", cmd.encode())  # Publish a stop command.
