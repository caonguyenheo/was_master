#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

void sensorCallBack(const sensor_msgs::Range::ConstPtr& msg)
{
        ROS_INFO("I heard: [%.2f]", msg->range);

}

int main(int argc, char **argv)
{
        ros::init(argc, argv, "master");

        ros::NodeHandle masterNode;
        ros::Subscriber range_sub = masterNode.subscribe("/was_sensor/range/ultrasound", 1000, sensorCallBack);

        ros::spin();
        
        return 0;
}
