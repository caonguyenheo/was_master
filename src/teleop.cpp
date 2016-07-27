#include "ros/ros.h"
#include "std_msgs/String.h"
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_RIGHT   0x43    //RIGHT_ARROW
#define KEYCODE_LEFT    0x44    //LEFT_ARROW
#define KEYCODE_UP      0x41    //UP_ARROW
#define KEYCODE_DOWN    0x42    //DOWN_ARROW
#define KEYCODE_STOP    0x20    //SPACE

class was_teleop
{
public:
        was_teleop();
        void keyLoop();

private:


        ros::NodeHandle nh_;
        ros::Publisher command_pub_;

};

was_teleop::was_teleop()
{
        command_pub_ = nh_.advertise<std_msgs::String>("was_control/moving", 1);
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
        bool dirty=false;


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

        std::string string_cmd;
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
                                string_cmd = "LEFT";
                                dirty = true;
                                break;
                        case KEYCODE_RIGHT:
                                ROS_DEBUG("RIGHT");
                                string_cmd = "RIGHT";
                                dirty = true;
                                break;
                        case KEYCODE_UP:
                                ROS_DEBUG("UP");
                                string_cmd = "UP";
                                dirty = true;
                                break;
                        case KEYCODE_DOWN:
                                ROS_DEBUG("DOWN");
                                string_cmd = "DOWN";
                                dirty = true;
                                break;
                        case KEYCODE_STOP:
                                ROS_DEBUG("STOP");
                                string_cmd = "STOP";
                                dirty = true;
                                break;
                }


                std_msgs::String cmd;
                cmd.data = string_cmd;
                if(dirty)
                {
                        command_pub_.publish(cmd);
                        dirty=false;
                }
        }
}