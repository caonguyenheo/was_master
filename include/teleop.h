#include "ros/ros.h"

class was_teleop
{
public:
        was_teleop();
        void keyLoop();

private:
        ros::NodeHandle nh_;
        ros::Publisher movement_pub_;
        ros::Publisher lift_pub_;
};

void quit(int sig);