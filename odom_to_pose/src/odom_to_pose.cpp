#include "ros/ros.h"
#include "geometry_msgs/PoseWithCovarianceStamped.h"
#include "nav_msgs/Odometry.h"
#include <iostream>

using namespace std;

ros::Publisher posePub;

void PoseCallback(const nav_msgs::Odometry &msg)
{
    geometry_msgs::PoseWithCovarianceStamped poseMsg;
    poseMsg.header = msg.header;
    poseMsg.pose = msg.pose;

    posePub.publish(poseMsg);
}

int main(int argc, char **argv) 
{
    ros::init(argc, argv, "odom_to_pose");
    ros::NodeHandle n;
    
    auto odomSub = n.subscribe("/mavros/local_position/odom", 1000, PoseCallback);
    posePub = n.advertise<geometry_msgs::PoseWithCovarianceStamped>("/odom_to_pose/pose_cov", 1000);

    cout << "Spinning" << endl;
    ros::spin();
    return 0;
}
