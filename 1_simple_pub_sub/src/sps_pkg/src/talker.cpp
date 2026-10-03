#include "ros/ros.h"
#include "sps_pkg/RobotData.h"


int main(int argc, char **argv)
{

ros::init(argc, argv, "talker");

    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<sps_pkg::RobotData>("/chatter",10,false);

    ros::Rate rate(10);
    while (ros::ok()){
        sps_pkg::RobotData msg;

        msg.name = "ZaraRobot";
        msg.battery_level = 82.5;
        msg.serial_num = 12451741;

        pub.publish(msg);
        ROS_INFO("Published: name=%s, battery=%.2f, serial=%d",
                 msg.name.c_str(),
                 msg.battery_level,
                 msg.serial_num);
                 
        rate.sleep();
    }


    return 0;
}



