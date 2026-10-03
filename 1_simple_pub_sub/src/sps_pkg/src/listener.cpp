#include "ros/ros.h"
#include "sps_pkg/RobotData.h"

void handle_msg(const sps_pkg::RobotData::ConstPtr& msg){
        ROS_INFO("Received: name=%s, battery=%.2f, serial=%d",
             msg->name.c_str(),
             msg->battery_level,
             msg->serial_num);


}



int main(int argc, char **argv){

    ros::init(argc, argv,"B_cpp");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/chatter",10,handle_msg);

    ros::spin();




    return 0;

}

