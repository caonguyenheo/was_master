#include "master.h"

was_master::was_master(void) {
                range_sub = nh.subscribe("/was_sensor/ultrasound",
                                         1000, &was_master::range_cb, this);
                lineTracking_sub = nh.subscribe("/was_sensor/lineTracking",
                                                1000, &was_master::lineTracking_cb, this);
                movement_sub = nh.subscribe("was_control/moving",
                                        1000, &was_master::movement_cb, this);
                lifting_sub = nh.subscribe("was_control/lifting",
                                        1000, &was_master::lifting_cb, this);
        }

void was_master::range_cb(const std_msgs::UInt16MultiArray::ConstPtr& msg) {
        for (int i = 0; i < 5; ++i)
        {
        	std::cout << "Rng[" << i << "]: " << msg->data.at(i) << " | ";
        }
        std::cout << std::endl;
}

void was_master::lineTracking_cb(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_DEBUG("Line Tracking value: [%d]", msg->data);
}

void was_master::movement_cb(const std_msgs::String::ConstPtr& cmd) {
        std::cout << cmd->data << std::endl;
}

void was_master::lifting_cb(const std_msgs::String::ConstPtr& cmd) {
	std::cout << cmd->data << std::endl;
}