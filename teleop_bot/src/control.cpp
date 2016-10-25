#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "geometry_msgs/Twist.h"
#include <boost/bind.hpp>

struct UnitStep{
    float linear = 1;
    float angular = 1;
};

void keyboardCallback(const std_msgs::Char::ConstPtr& msg, ros::Publisher pub, UnitStep unit_step){ 
    geometry_msgs::Twist cmd_msg;

    switch(msg->data){
        case 'C' : //left arrow
            ROS_DEBUG("right arrow");
            cmd_msg.angular.z = -1*unit_step.angular; 
            break;
        case 'A' : //up arrow
            ROS_DEBUG("up arrow"); 
            cmd_msg.linear.x = unit_step.linear; 
            break;
        case 'D' ://right arrow
            ROS_DEBUG("left arrow"); 
            cmd_msg.angular.z = unit_step.angular; 
            break;
        case 'B' : //down arrow
            ROS_DEBUG("down arrow"); 
            cmd_msg.linear.x = -1*unit_step.linear; 
            break;
        default :
            break;
    }

    pub.publish(cmd_msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "control");
    ros::NodeHandle n;
    ros::Publisher command_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    struct UnitStep unit_step;
    n.param<float>("unit_linear", unit_step.linear, 1.0);
    n.param<float>("unit_angular",unit_step.angular, 1.0);
    ros::Subscriber sub = n.subscribe<std_msgs::Char>("keyboard", 1, boost::bind(keyboardCallback, _1, command_pub, unit_step));
    ros::spin();
    return 0;
}
