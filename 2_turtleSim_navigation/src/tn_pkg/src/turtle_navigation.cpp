#include <ros/ros.h>
#include <geometry_msgs/Twist.h>  // For commanding turtle movement (cmd_vel)
#include <turtlesim/Pose.h>       // For reading the turtle's position/orientation
#include <cmath>
#include <std_srvs/Empty.h> 
#include <turtlesim/Spawn.h>
#include <turtlesim/SetPen.h>


float goal_x;
float goal_y;
float current_x;
float current_y;
float current_theta;

float turtle2_x;
float turtle2_y;
float turtle2_theta;

bool goal_reached=false;

ros::Publisher pubt1;
ros::Publisher pubt2;
ros::ServiceClient srvc;
ros::ServiceClient trsp;
ros::ServiceClient chpen;


void poseCallback(const turtlesim::Pose& posemsg){

    current_x = posemsg.x;
    current_y = posemsg.y;
    current_theta = posemsg.theta;

    float dx = goal_x - current_x;
    float dy = goal_y - current_y;

    float dx_square = dx * dx;
    float dy_square = dy * dy;

    float distance = std::sqrt((dx_square + dy_square));

    float target_angle = std::atan2(dy,dx);
    float angle_error = target_angle - current_theta;

    geometry_msgs::Twist tm;
    


    if (distance<0.1){
        tm.linear.x=0;
        tm.linear.y=0;
        tm.angular.z = 0;
        ROS_INFO_ONCE("turtle1 said: Goal Reached!!");
    }else{
        tm.linear.x = 0.2 * distance;
        tm.angular.z = 0.5 * angle_error;
    }

    pubt1.publish(tm);

   



}


void hundle_turtle2(const turtlesim::Pose& posemsgt2){
    turtle2_theta = posemsgt2.theta;
    turtle2_x = posemsgt2.x;
    turtle2_y = posemsgt2.y;

    float dx = current_x - turtle2_x;
    float dy = current_y - turtle2_y;

    float dx_square = dx * dx;
    float dy_square = dy * dy;

    float distance = std::sqrt((dx_square + dy_square));

    float target_angle = std::atan2(dy,dx);
    float angle_error = target_angle - turtle2_theta;

    geometry_msgs::Twist t2m;


    if (distance<0.1 && !goal_reached){
        t2m.linear.x=0;
        t2m.linear.y=0;
        t2m.angular.z = 0;
        ROS_INFO_ONCE("turtle_2 said: Goal Reached!!");
        goal_reached=true;
        std_srvs::Empty srv;
        srvc.call(srv);
    }else{
        t2m.linear.x = 0.2 * distance;
        t2m.angular.z = 0.5 * angle_error;
    }

    pubt2.publish(t2m);



}


int main(int argc, char **argv){
    ros::init(argc,argv,"turtle_navigation");
    ros::NodeHandle nh;
    ros::NodeHandle pnh("~");

    pubt1 = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
    pubt2 = nh.advertise<geometry_msgs::Twist>("/turtle2/cmd_vel",10);

    ros::Subscriber sub1 = nh.subscribe("/turtle1/pose",10,poseCallback);
    ros::Subscriber sub2 = nh.subscribe("/turtle2/pose",10,hundle_turtle2);

    srvc = nh.serviceClient<std_srvs::Empty>("/clear");

    trsp = nh.serviceClient<turtlesim::Spawn>("/spawn");
    trsp.waitForExistence();
    turtlesim::Spawn t2;
    t2.request.name="turtle2";
    t2.request.x=1;
    t2.request.y=1;
    t2.request.theta=0;
    trsp.call(t2);

    chpen = nh.serviceClient<turtlesim::SetPen>("/turtle2/set_pen");
    chpen.waitForExistence();
    turtlesim::SetPen sp;
    sp.request.r=225;
    sp.request.g=0;
    sp.request.b=0;
    sp.request.width=5;

    chpen.call(sp);

    pnh.param("goal_x",goal_x,8.0f);
    pnh.param("goal_y",goal_y,8.0f);

    


    ros::spin();



    return 0;
}