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
 #include <unistd.h>

 #ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif

double                 vl,vr;
int                 left_dir , right_dir , encoder_request_button;
double              linear_x,angular_z;
bool                stop_published =false;
dumbo::Controller   *controller;

void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg) {
 /*
    CHANGE SOME GLOBAL VAR WHICH IS USE IN CONTROLLOOP()
 */
  linear_x = msg->linear.x;
  angular_z = msg->angular.z;
  //encoder_request_button = msg->linear.y;
}
 
void control_loop(){
  
  if(linear_x == 0 && angular_z == 0) {
      std::cout << "[STOP] ";
      controller->send_stop();
  }
  if(linear_x != 0 && angular_z == 0){
        int linearDirection,velocity;
        if(linear_x > 0){
           std::cout<<"[FORWARD]";
            linearDirection = 1;
            velocity = linear_x;
        }else{
            std::cout<<"[BACKWARD]";
            linearDirection = 2; 
            velocity = -linear_x;
        }
  controller->driveTutor(velocity,linearDirection,velocity,linearDirection); 
  }
  else if(angular_z != 0 && linear_x == 0 ){
        int dir_left,dir_right,velocity;
        if(angular_z > 0){ // SpinLeft
            std::cout<<"[LEFT]";
            dir_left = 2;
            dir_right = 1;
            velocity = angular_z;
        }else{
            std::cout<<"[RIGHT]";
            dir_left = 1;
            dir_right = 2;
            velocity = -angular_z;
        }
  controller->driveTutor(velocity,dir_left,velocity,dir_right);
  }
  controller->send_read_encoder();
  controller->read_encoder();
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

  int command_vl = (vl/0.25)*255;
  int command_vr = (vr/0.25)*255;

  // Absolute
  command_vl = (command_vl < 0 )? -command_vl:command_vl; 
  command_vr = (command_vr < 0 )? -command_vr:command_vr; 
  // Send Drive Command
  controller->driveDirect(command_vl,left_dir,command_vr,right_dir);

  // Request to Read Encoder Everytime That Driving Command Sends
  controller->send_read_encoder();
  controller->read_encoder();
  std::cout << "D_L = " << left_dir << "  SEND V-L = " << command_vl << std::endl;
  std::cout << "D_R = " << right_dir << " SEND V-R = " << command_vr << std::endl;

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
    //ros::

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
           }
              //Main Control Loop
              //control_loop();
              control_loop_cmd_vel();
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