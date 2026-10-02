#!/usr/bin/env python

import rospy
from sps_pkg.msg import RobotData


def handle_msg(msg):
    print(f"there's a msg on the topic: \n{msg}")
    


if __name__ == "__main__":
    rospy.init_node("B")
    sub = rospy.Subscriber("/chatter",RobotData,handle_msg)
    rospy.spin()

