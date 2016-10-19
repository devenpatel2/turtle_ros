#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "keypress/keypress.h"
int main(int argc, char **argv){
    
    ros::init(argc, argv, "keyboard");
    ros::NodeHandle n;
    ros::Publisher keyPub = n.advertise<std_msgs::Char>("keyboard", 1);
    ros::Rate loop_rate(100);    
    
    std_msgs::Char msg;
    while(ros::ok()){
       
        msg.data = getch();
        ROS_INFO("%c", msg.data);
        keyPub.publish(msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
