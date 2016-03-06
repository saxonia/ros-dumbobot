/*********************************************************************
ros-dumbobot Twist To Motor Node
Author : Theppasith Nisitsukcharoen
<theppasith@gmail.com , Theppasith.N@Student.chula.ac.th>
Department of Computer Engineering , Chulalongkorn University
*********************************************************************/

#include <string>
#include <iostream>
#include <ros/ros.h>
#include <termios.h>
#include <geometry_msgs/Twist.h>

//Odom and tf
#include <geometry_msgs/Vector3.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Float32.h>

//Global Variable
double	linear_x;
double	angular_z;

std_msgs::Float32 lwheel_vtarget,rwheel_vtarget;

void cmd_velCallback(const geometry_msgs::Twist::ConstPtr& msg) {
 /*
    CHANGE SOME GLOBAL VAR WHICH IS USE IN CONTROLLOOP()
 */
  linear_x = msg->linear.x;
  angular_z = msg->angular.z;

  if(linear_x == -0.00)linear_x = 0;
  if(angular_z == -0.00)angular_z = 0;

}

void calculation_loop(){

  // Params
	double width_robot = 0.4; //40 CM from Wheel to Wheel
	double wheelRadius = 0.095; //9.5 CM Wheel Center to Circumference
	double wheel_separation_multiplier = 1.6;
	double wheel_separation = width_robot * wheel_separation_multiplier; //Wheel Separation

  // Compute wheels velocities:
	const double vel_left  = (linear_x- angular_z * wheel_separation / 2.0);
	const double vel_right = (linear_x+ angular_z * wheel_separation / 2.0);

 	lwheel_vtarget.data = vel_left;
 	rwheel_vtarget.data = vel_right;
}

 /*
 *   Main Loop of This Node
 */
 int main(int argc, char **argv){

  // Create Node Called "ros_dumbobot_twist_to_motor"
    ros::init(argc, argv, "ros_dumbobot_twist_to_motor");
    ros::NodeHandle nh("~");

  // Subscribe to Command Velocity
    ros::Subscriber sub = nh.subscribe("/ros_dumbobot/cmd_vel", 1, cmd_velCallback);

  // Publish the Setpoint Of the Motor
    ros::Publisher wheel_encoder_pub = nh.advertise<geometry_msgs::Vector3>("wheel_encoder", 100);
    ros::Publisher lwheel_vtarget_pub = nh.advertise<std_msgs::Float32>("/ros_dumbobot/lwheel_vtarget", 100);
    ros::Publisher rwheel_vtarget_pub = nh.advertise<std_msgs::Float32>("/ros_dumbobot/rwheel_vtarget", 100);
    
  // Spinner which poll for callback
    ros::AsyncSpinner spinner(50);
    spinner.start(); 

  // Start the Main Loop
    while (ros::ok()) {
      calculation_loop();
       // Publish The Setpoint Of Vel_left and Vel_right To PID Controller 
      lwheel_vtarget_pub.publish(lwheel_vtarget);
      rwheel_vtarget_pub.publish(rwheel_vtarget);
    }
    //End Loop
    spinner.stop();
    return 0;

}