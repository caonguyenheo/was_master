#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/Range.h"

void range_sensor_callback(const sensor_msgs::Range::ConstPtr& msg) {
        ROS_INFO("Range: [%.2f] mm", msg->range);

}

void lineTracking_sensor_callback(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_INFO("Line Tracking value: [%d]", msg->data);
}

class was_master{
private:
        ros::NodeHandle nh;
        ros::Subscriber range_sub;
        ros::Subscriber lineTracking_sub;

public:
        was_master() {
                range_sub = nh.subscribe("/was_sensor/range/ultrasound",
                                        1000, range_sensor_callback);
                lineTracking_sub = nh.subscribe("/was_sensor/movement/lineTracking",
                                        1000, lineTracking_sensor_callback);
        }

};

int main(int argc, char **argv) {
        ros::init(argc, argv, "master");

        was_master wasMaster = was_master();

        ros::spin();
        
        return 0;
}
