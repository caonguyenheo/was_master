#include "ros/ros.h"
#include "std_msgs/String.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>

// For moving
#define KEYCODE_RIGHT           0x64    // D
#define KEYCODE_LEFT            0x61    // A
#define KEYCODE_FORWARD         0x77    // W
#define KEYCODE_BACKWARD        0x73    // S

// For lift
#define KEYCODE_UP              0x65    // E
#define KEYCODE_DOWN            0x63    // C

// For both lift and moving
#define KEYCODE_STOP            0x20    // SPACE

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

was_teleop::was_teleop()
{
        movement_pub_ = nh_.advertise<std_msgs::String>("was_control/movement", 1);
        lift_pub_ = nh_.advertise<std_msgs::String>("was_control/lift", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
        (void)sig;
        tcsetattr(kfd, TCSANOW, &cooked);
        ros::shutdown();
        exit(0);
}


int main(int argc, char** argv)
{
        ros::init(argc, argv, "was_teleop");
        was_teleop teleop_cmd;

        signal(SIGINT,quit);

        teleop_cmd.keyLoop();

        return(0);
}


void was_teleop::keyLoop()
{
        char c;
        bool is_moving=false;
        bool is_lifting=false;


        // get the console in raw mode
        tcgetattr(kfd, &cooked);
        memcpy(&raw, &cooked, sizeof(struct termios));
        raw.c_lflag &=~ (ICANON | ECHO);
        // Setting a new line, then end of file
        raw.c_cc[VEOL] = 1;
        raw.c_cc[VEOF] = 2;
        tcsetattr(kfd, TCSANOW, &raw);

        puts("Reading from keyboard");
        puts("---------------------------");
        puts("Use arrow keys to move the turtle.");

        std::string movement_cmd;
        std::string lift_cmd;
        while(1)
        {
                // get the next event from the keyboard
                if(read(kfd, &c, 1) < 0)
                {
                        perror("read():");
                        exit(-1);
                }

                ROS_DEBUG("value: 0x%02X\n", c);

                std::cout << "Pressing: " << std::hex << std::showbase << (int) c << std::endl;

                switch(c)
                {
                        case KEYCODE_LEFT:
                                ROS_DEBUG("LEFT");
                                movement_cmd = "LEFT";
                                is_moving = true;
                                break;
                        case KEYCODE_RIGHT:
                                ROS_DEBUG("RIGHT");
                                movement_cmd = "RIGHT";
                                is_moving = true;
                                break;
                        case KEYCODE_FORWARD:
                                ROS_DEBUG("FORWARD");
                                movement_cmd = "FORWARD";
                                is_moving = true;
                                break;
                        case KEYCODE_BACKWARD:
                                ROS_DEBUG("BACKWARD");
                                movement_cmd = "BACKWARD";
                                is_moving = true;
                                break;
                        case KEYCODE_UP:
                                ROS_DEBUG("LIFT_UP");
                                lift_cmd = "LIFT_UP";
                                is_lifting = true;
                                break;
                        case KEYCODE_DOWN:
                                ROS_DEBUG("LIFT_DOWN");
                                lift_cmd = "LIFT_DOWN";
                                is_lifting = true;
                                break;
                        case KEYCODE_STOP:
                                ROS_DEBUG("STOP");
                                movement_cmd = "STOP";
                                is_moving = true;
                                is_lifting = true;
                                break;
                }


                if (is_moving) {
                        std_msgs::String cmd;
                        cmd.data = movement_cmd;
                        movement_pub_.publish(cmd);
                        is_moving=false;
                }
                if (is_lifting) {
                        std_msgs::String cmd;
                        cmd.data = lift_cmd;
                        lift_pub_.publish(cmd);
                        is_lifting=false;
                }
        }
}
