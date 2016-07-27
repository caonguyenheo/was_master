#include "master.h"

void was_master::range_cb(const sensor_msgs::Range::ConstPtr& msg) {
        ROS_DEBUG("Range: [%.2f] mm", msg->range);
}

void was_master::lineTracking_cb(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_DEBUG("Line Tracking value: [%d]", msg->data);
}

void was_master::teleop_cb(const std_msgs::String::ConstPtr& cmd) {
        std::cout << cmd->data << std::endl;
}
