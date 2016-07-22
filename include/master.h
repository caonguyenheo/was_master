#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "sensor_msgs/Range.h"

class was_master{
private:
        ros::NodeHandle nh;
        ros::Subscriber range_sub;
        ros::Subscriber lineTracking_sub;
        void range_cb(const sensor_msgs::Range::ConstPtr& msg);
        void lineTracking_cb(const std_msgs::UInt32::ConstPtr& msg);


public:
        was_master() {
                range_sub = nh.subscribe("/was_sensor/range/ultrasound",
                                         1000, &was_master::range_cb, this);
                lineTracking_sub = nh.subscribe("/was_sensor/movement/lineTracking",
                                                1000, &was_master::lineTracking_cb, this);
        }
        
};
