#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

/*************************************************************************************/
class TeleopTurtle
{
public:
  TeleopTurtle();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  
  ros::NodeHandle nh_;

  bool stop_state;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher twist_pub_;
  ros::Subscriber joy_sub_;
  
};

//END CLASS
/*************************************************************************************/

TeleopTurtle::TeleopTurtle():
  linear_(1),
  angular_(2)
{
	//param ("NAME" , VAR , VAR );
  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  twist_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);

}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  //Encoder Reading Joystick Button
  int encoder_request_button;
    

  //Geometry Joystick Control
  geometry_msgs::Twist twist;
  int deadman_triggered;
  //Read Value From Right Joystick (HORIZONTAL ACCESS ONLY)
  twist.angular.z = a_scale_*joy->axes[angular_];
  //Read Value From Left Joystick (VERTICAL ACCESS ONLY)
  twist.linear.x = l_scale_*joy->axes[linear_];
  deadman_triggered = joy->axes[2];

  //Piggybackked msg with linear.y
    twist.linear.y = joy->buttons[0];
  //ONLY ONE VALUE CAN BE PASSED
  if(twist.angular.z !=0  && twist.linear.x != 0){
    stop_state = true;
  }else{
    stop_state = false;
  }

  //Publish Velocity
  if(stop_state){ //STOP STATE == PRODUCE STOP
    twist_pub_.publish(*new geometry_msgs::Twist());
  }else if (!stop_state && deadman_triggered == -1){
    twist_pub_.publish(twist);
  }

/*//PROCESS VALUE FOR DRIVING ( LINEAR , ANGULAR ) HERE !!! 
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];

  //Publish Velocity
  twist_pub_.publish(twist);
*/

}


int main(int argc, char** argv)
{
  //Node Name  = "teleop_turtle"  (can be override by LAUNCHFILE)
  ros::init(argc, argv, "teleop_turtle");
  TeleopTurtle teleop_turtle;
  ros::spin();
}
