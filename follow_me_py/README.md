# Follow Me (Python)

Edit the file `follow_me.py` to write a program that keeps the robot a fixed distance away from a target directly in front of it.

## Usage

To run the code, do:
```bash
python follow_me.py
```
Press `Ctrl+C` on your keyboard to stop the code. This should stop the robot.

## Programming with LCM

Use the [LCM Python tutorial](https://lcm-proj.github.io/lcm/content/tutorial-python.html) to learn how to program with LCM (skip the part on generating messages - you will use the pre-installed MBot LCM messages).

### Available Messages and Channels

You can import messages from the package `mbot_lcm_msgs` as follows:
```py
from mbot_lcm_msgs import pose2D_t
```
This library is already installed on full images. See all the available messages [here](https://github.com/mbot-project/mbot_lcm_base/tree/main/mbot_msgs/lcmtypes).

To see all the channels currently being published by your robot, open your browser and navigate to `http://<MBOT-IP>/spy`, replacing all of `<MBOT-IP>` with the IP address of your MBot.

### Driving the Robot

To drive the MBot, publish a `mbot_lcm_msgs.twist2D_t` message to the topic `"MBOT_VEL_CMD"`.
