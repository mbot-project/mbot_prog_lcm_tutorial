# Follow Me (C++)

Edit the file `src/follow_me.cpp` to write a program that keeps the robot a fixed distance away from a target directly in front of it.

## Usage

To build the code, do:
```bash
cd follow_me_cpp/build
cmake ..
make
```
To run the code, do:
```bash
./follow_me
```
Press `Ctrl+C` on your keyboard to stop the code. This should stop the robot.

## Programming with LCM

Use the [LCM C++ tutorial](https://lcm-proj.github.io/lcm/content/tutorial-cpp.html) to learn how to program with LCM (skip the part on generating messages - you will use the pre-installed MBot LCM messages).

### Available Messages and Channels

You can import messages from the package `mbot_lcm_msgs` as follows:
```cpp
#include <mbot_lcm_msgs/pose2D_t.hpp>
```
This library is already installed on full images. See all the available messages [here](https://github.com/mbot-project/mbot_lcm_base/tree/main/mbot_msgs/lcmtypes).

To see all the channels currently being published by your robot, open your browser and navigate to `http://<MBOT-IP>/spy`, replacing all of `<MBOT-IP>` with the IP address of your MBot.

### Driving the Robot

To drive the MBot, publish a `mbot_lcm_msgs::twist2D_t` message to the topic `"MBOT_VEL_CMD"`.
