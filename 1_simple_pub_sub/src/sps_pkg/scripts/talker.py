#!/usr/bin/env python

import rospy
from sps_pkg.msg import RobotData

rospy.init_node("A")
pub = rospy.Publisher("/chatter",RobotData,queue_size=10)
rate = rospy.Rate(1)

while not rospy.is_shutdown():
    rd=RobotData()
    rd.name="zararobot"
    rd.battery_level=82.5
    rd.serial_num=12451741
    pub.publish(rd)
    rate.sleep()
    