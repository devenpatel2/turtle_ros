#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "geometry_msgs/Twist.h"
#include <boost/bind.hpp>


void keyboardCallback(const std_msgs::Char::ConstPtr& msg, ros::Publisher pub){ 
    switch(msg->data){
        case 'C' : //left arrow
            ROS_INFO("left arrow");
            break;
        case 'A' : //up arrow
            ROS_INFO("up arrow"); 
            break;
        case 'D' ://right arrow
            ROS_INFO("right arrow"); 
            break;
        case 'B' : //down arrow
            ROS_INFO("down arrow"); 
            break;
        default :
            break;
    }
}

int main(int argc, char **argv){
    ros::init(argc, argv, "control");
    ros::NodeHandle n;
    ros::Publisher command_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    ros::Subscriber sub = n.subscribe<std_msgs::Char>("keyboard", 1, boost::bind(keyboardCallback, _1, command_pub));
    ros::spin();
    return 0;
}
