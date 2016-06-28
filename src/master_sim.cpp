#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

void sensorCallBack(const sensor_msgs::Range::ConstPtr& msg)
{
//        ROS_INFO("I heard: [%s]", msg->data.c_str());

}

int main(int argc, char **argv)
{
        boost::shared_ptr<std_msgs::String> range_msg;
        ros::init(argc, argv, "master");

        ros::NodeHandle masterNode;
        ros::Subscriber range_sub = masterNode.subscribe("/was_sensor/range/ultrasound", 1000, sensorCallBack);

        ros::spin();
        
        return 0;
}
