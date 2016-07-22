#include "master.h"

void was_master::range_cb(const sensor_msgs::Range::ConstPtr& msg) {
        ROS_INFO("Range: [%.2f] mm", msg->range);

}

void was_master::lineTracking_cb(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_INFO("Line Tracking value: [%d]", msg->data);
}