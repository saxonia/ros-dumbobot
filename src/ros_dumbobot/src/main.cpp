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

int                 left_speed,right_speed;
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
  encoder_request_button = msg->linear.y;
}
 
void control_loop(){
  
  // if(encoder_request_button == 1){
  //   controller->send_read_encoder();
  //   controller->read_encoder();
  //   return;
  // }


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

  //READ FROM read_buffer
  // int readed = controller->read_drive_command();
  //   if(readed != 12){
  //     ROS_ERROR_STREAM_ONCE("READ IS = " << readed);
  //   }else{
  //     std::cout << "command readed = " << readed << "bytes   ";
  //   }
  controller->send_read_encoder();
  controller->read_encoder();
}


/*
 * Main Loop of This Node
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

    ros::Subscriber sub = nh.subscribe("/turtle1/cmd_vel", 1, cmd_velCallback);

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
                control_loop();
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