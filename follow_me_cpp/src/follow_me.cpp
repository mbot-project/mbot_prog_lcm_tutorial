#include <cmath>
#include <string>
#include <vector>
#include <iostream>
#include <signal.h>

#include <lcm/lcm-cpp.hpp>
#include <mbot_lcm_msgs/lidar_t.hpp>
#include <mbot_lcm_msgs/twist2D_t.hpp>

bool ctrl_c_pressed;
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

/**
 * Finds the distance to the nearest object in front of the robot by averaging
 * a few forward-pointing rays.
 */
float findFwdDist(const std::vector<float>& ranges, const std::vector<float>& thetas)
{
    // Simple average filter over the front rays in case a few are invalid.
    int num_range = 5;
    // Check for invalid vector lengths.
    if (ranges.size() < num_range || thetas.size() < num_range)  return -1;

    int num_scans = 0;
    float sum = 0;

    // Read the first few rays.
    for (int i = 0; i < num_range; ++i) {
        if (ranges[i] > 0) {
            sum += ranges[i] * cos(thetas[i]);
            num_scans++;
        }
    }
    // Read the last few rays.
    for (int i = ranges.size() - num_range; i < ranges.size(); ++i) {
        if (ranges[i] > 0) {
            sum += ranges[i] * cos(thetas[i]);
            num_scans++;
        }
    }

    // If we didn't find any valid scans, return an invalid value.
    if (num_scans < 1) return -1;

    return sum / num_scans;  // Return the average distance.
}


class FollowMe {
public:
    FollowMe() :
        lcm_("udpm://239.255.76.67:7667?ttl=1")  // Create the LCM object.
    {
        // Subscribe to the Lidar message.
        lcm_.subscribe("LIDAR", &FollowMe::handleLidar, this);
    }

    void handle() {
        lcm_.handleTimeout(500);  // Handle incoming messages, with a timeout.
    }

    void handleLidar(const lcm::ReceiveBuffer* rbuf,
                     const std::string& ch,
                     const mbot_lcm_msgs::lidar_t* msg)
    {
        // Get the forward distance.
        float dist_to_wall = findFwdDist(msg->ranges, msg->thetas);

        // TODO: Write code to implement the Follow Me controller when a lidar scan comes in.
    }

private:
    lcm::LCM lcm_;
};

int main(int argc, char ** argv)
{
    ctrl_c_pressed = false;
    signal(SIGINT, ctrlc);
    signal(SIGTERM, ctrlc);

    FollowMe follower;

    // Loop forever.
    while(!ctrl_c_pressed) {
        follower.handle();
    }

    std::cout << "Stopping the MBot!" << std::endl;

    // Stop the robot before quitting.
    lcm::LCM lcm("udpm://239.255.76.67:7667?ttl=1");
    mbot_lcm_msgs::twist2D_t cmd;
    cmd.vx = cmd.vy = cmd.wz = 0;
    lcm.publish("MBOT_VEL_CMD", &cmd);

    return 0;
}
