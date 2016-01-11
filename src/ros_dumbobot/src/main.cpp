/*********************************************************************
ros-dumbobot Node
Author : Theppasith Nisitsukcharoen
<theppasith@gmail.com , Theppasith.N@Student.chula.ac.th>
Department of Computer Engineering , Chulalongkorn University
*********************************************************************/

/**
 * Node entry-point locates Here !
 * Handles ROS setup, and serial port connection/reconnection.
**/
#include <string>
#include "ros_dumbobot/controller.h"
#include <iostream>
#include <ros/ros.h>
#include <termios.h>
#include <geometry_msgs/Twist.h>

//Odom and tf
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>


 #ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif

double              vl,vr;
int                 left_dir , right_dir , encoder_request_button;
double              linear_x,angular_z;
bool                stop_published =false;
dumbo::Controller   *controller;

ros::Time current_time_encoder, last_time_encoder;
double oneMetre = 4975;
double oneRound = 3125;
//Odom and tf 
geometry_msgs::Vector3 ticks;
double tick,last_tick;
void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg) {
 /*
    CHANGE SOME GLOBAL VAR WHICH IS USE IN CONTROLLOOP()
 */
  linear_x = msg->linear.x;
  angular_z = msg->angular.z;
}

void test(){

    while(true){
      controller->driveTutor(255,1,255,1);
      controller->send_read_encoder();
      //ticks = controller->read_encoder();
      tick = controller->readtick();
      std::cout << "tick = " << tick <<std::endl;
      std::cout << "tickmod = " << (int)tick % 4975 <<std::endl;
      if((int)tick % (int)oneRound < 100 && (int)tick >500){
        break;
      }
    }

  controller->send_stop();
  controller->send_read_encoder();
  controller->read_encoder();

  usleep(5000 * 1000);

  } 

void control_loop_cmd_vel(){
  // Scaling =>> X [0-2.5] m/s
  // Scaling =>> th [ 0 - 1.25 ] rad/s
  double vel_x = linear_x;
  double vel_th = angular_z;
  double width_robot = 0.4; //40 CM from Wheel to Wheel
  double wheelRadius = 0.095; //9.5 CM Wheel Center to Circumference

  double velDiff = (width_robot * vel_th) / 2.0;
  double leftPower = (vel_x - velDiff);
  double rightPower = (vel_x + velDiff);

  vl = leftPower ; 
  vr = rightPower ;

  vl = MAX(vl , -0.25);
  vr = MAX(vr , -0.25);
  vl = MIN(vl , 0.25);
  vr = MIN(vr , 0.25);

  left_dir = (vl < 0)? 2:1;
  right_dir = (vr < 0)? 2:1;

  // Scaler to meet Byte
  int command_vl = (vl/0.25)*255;
  int command_vr = (vr/0.25)*255;

  // Absolute
  command_vl = (command_vl < 0 )? -command_vl:command_vl; 
  command_vr = (command_vr < 0 )? -command_vr:command_vr; 
  // Send Drive Command
  controller->driveDirect(command_vl,left_dir,command_vr,right_dir);

  // Request to Read Encoder Everytime That Driving Command Sends
  controller->send_read_encoder();
  ticks = controller->read_encoder();
}


/*
 *   Main Loop of This Node
 */
 int main(int argc, char **argv){

  // Create Node Called "ros_dumbobot"
    ros::init(argc, argv, "ros_dumbobot");
    ros::NodeHandle nh("~");

  // Serial Setting
    std::string port = "/dev/ttyACM0";
    int32_t baud = 9600;
    nh.param<std::string>("port", port, port);
    nh.param<int32_t>("baud", baud, baud);
    ROS_INFO("DUMBOBOT connecting to port %s", port.c_str());

  // Subscribe to Joystick Command
    ros::Subscriber sub = nh.subscribe("/turtle1/cmd_vel", 1, cmd_velCallback);

  // Publish the Encoder Data
    ros::Publisher wheel_encoder_pub = nh.advertise<geometry_msgs::Vector3>("wheel_encoder", 100);

  // Interface to ATMEGA128 and Motor Controller
    controller = new dumbo::Controller(port.c_str(),baud);
    bool initialize = false;
    
  // Spinner which poll for callback
    ros::AsyncSpinner spinner(50);
    spinner.start(); 

  // Start the Main Loop
    while (ros::ok()) {
      ROS_DEBUG("Attempting connection to %s at %i baud.", port.c_str(), baud);
      if(!controller->connected()){
        controller->connect(); 
      }
      if (controller->connected()) {
        // Single time Initializer
           if(!initialize){
              //One Second Booting
                sleep(1);
              controller->spinOnce(); //Clear Everything that is on the buffer( Clear size = 50)
              ROS_INFO("DUMBOBOT Booting Finished");
              initialize = true;
              //test();
           }
              //Main Control Loop
              //control_loop();
              control_loop_cmd_vel();
              wheel_encoder_pub.publish(ticks);
              usleep(10*1000);
      } else {
        ROS_DEBUG("Problem connecting to serial device.");
        ROS_ERROR_STREAM_ONCE("Problem connecting to port " << port << ". Trying again every 1 second.");
        sleep(1);
      }
    }
    //End Loop
    spinner.stop();
    controller->send_stop();
    return 0;

}