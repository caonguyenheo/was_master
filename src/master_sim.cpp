#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/Range.h"

void range_sensor_callback(const sensor_msgs::Range::ConstPtr& msg) {
        ROS_INFO("Range: [%.2f] mm", msg->range);

}

void lineTracking_sensor_callback(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_INFO("Line Tracking value: [%d]", msg->data);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "master");

        ros::NodeHandle masterNode;
        ros::Subscriber range_sub = masterNode.subscribe("/was_sensor/range/ultrasound", 1000, range_sensor_callback);
        ros::Subscriber lineTracking_sub = masterNode.subscribe("/was_sensor/movement/lineTracking", 1000, lineTracking_sensor_callback);

        ros::spin();
        
        return 0;
}
