/*********************************************************************
ros-dumbobot-waypoint-navigation Node
Author : Theppasith Nisitsukcharoen
<theppasith@gmail.com , Theppasith.N@Student.chula.ac.th>
Department of Computer Engineering , Chulalongkorn University
*********************************************************************/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <vector>
#include <geometry_msgs/Pose2D.h>


//Client Service of move_base 
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//Global Variable
bool sendNewGoal;
bool finish;

//Waypoints 
//std::vector<geometry_msgs::Pose2D>            targets;
//std::vector<geometry_msgs::Pose2D>::iterator  target;
std::vector<move_base_msgs::MoveBaseGoal>           targets;
std::vector<move_base_msgs::MoveBaseGoal>::iterator target;

void read_waypoint_from(std::string filename){
  move_base_msgs::MoveBaseGoal point1;
  point1.target_pose.pose.position.x    = -1;
  point1.target_pose.pose.position.y    = 2;
  point1.target_pose.pose.orientation.x = 0;
  point1.target_pose.pose.orientation.y = 0;
  point1.target_pose.pose.orientation.z = 0.016;
  point1.target_pose.pose.orientation.w = 0.9;
  targets.push_back(point1);

  move_base_msgs::MoveBaseGoal point2;
  point2.target_pose.pose.position.x    = 4;
  point2.target_pose.pose.position.y    = 2;
  point2.target_pose.pose.orientation.x = 0;
  point2.target_pose.pose.orientation.y = 0;
  point2.target_pose.pose.orientation.z = 0.7;
  point2.target_pose.pose.orientation.w = 0.7;
  targets.push_back(point2);


  move_base_msgs::MoveBaseGoal point3;
  point3.target_pose.pose.position.x    = 3.9;
  point3.target_pose.pose.position.y    = -1.9;
  point3.target_pose.pose.orientation.x = 0;
  point3.target_pose.pose.orientation.y = 0;
  point3.target_pose.pose.orientation.z = -0.4;
  point3.target_pose.pose.orientation.w = 0.91;
  targets.push_back(point3);

  move_base_msgs::MoveBaseGoal point4;
  point4.target_pose.pose.position.x    = -1;
  point4.target_pose.pose.position.y    = -2;
  point4.target_pose.pose.orientation.x = 0;
  point4.target_pose.pose.orientation.y = 0;
  point4.target_pose.pose.orientation.z = 0.7;
  point4.target_pose.pose.orientation.w = 0.7;
  targets.push_back(point4);

  move_base_msgs::MoveBaseGoal point5;
  point5.target_pose.pose.position.x    = 1.695;
  point5.target_pose.pose.position.y    = 0.066;
  point5.target_pose.pose.orientation.x = 0;
  point5.target_pose.pose.orientation.y = 0;
  point5.target_pose.pose.orientation.z = 0.9;
  point5.target_pose.pose.orientation.w = 0;
  targets.push_back(point5);

}


void goalDoneCallback(const actionlib::SimpleClientGoalState &state, 
  const move_base_msgs::MoveBaseResultConstPtr &result){

    if(state.state_ == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The goal was reached!");

    if(state.state_ == actionlib::SimpleClientGoalState::ABORTED)
        ROS_WARN("Failed to reach the goal...");

    // Send next Target
    target++;
    sendNewGoal = true;
    if(target==targets.end()){
      //Return to Beginning
        //target=targets.begin();
      finish = true;
    } 
}


void goalActiveCallback(){
  //ROS_INFO("Goal active! Hurray!");
}


void goalFeedbackCallback(const move_base_msgs::MoveBaseFeedbackConstPtr &feedback){
  //ROS_INFO("Getting feedback! How cool is that?");
}


int main(int argc, char** argv){
  ros::init(argc, argv, "simple_navigation_goals");

  // Tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Read waypoint from file to vector
  read_waypoint_from("waypoints.txt");
  target = targets.begin();
  ROS_INFO("Load waypoints Successfully targets");
  //Callback polling Rate 
  ros::Rate r(10);
  bool online = true;

  int tries = 0;
  // Wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
    tries++;
    if(tries == 3){
      online = false;
      break;
    }
  }
  ROS_INFO("Navigation Waypoint Node Initialized !");
  sendNewGoal = true;
  // Start the Navigation Waypoint Loop
    while(ros::ok() && !finish && online ){

      // The Next Goal ! 
      if(sendNewGoal){

          // Do this Target until its end
          sendNewGoal = false;

          // Move base Goal
          move_base_msgs::MoveBaseGoal goal;
        
          // Send a goal to the robot
          goal.target_pose.header.frame_id = "/map";
          goal.target_pose.header.stamp = ros::Time::now();
        
          // Set the goal
          goal.target_pose.pose.position.x    = target->target_pose.pose.position.x;
          goal.target_pose.pose.position.y    = target->target_pose.pose.position.y;
          goal.target_pose.pose.orientation.x = target->target_pose.pose.orientation.x;
          goal.target_pose.pose.orientation.y = target->target_pose.pose.orientation.y;
          goal.target_pose.pose.orientation.z = target->target_pose.pose.orientation.z;
          goal.target_pose.pose.orientation.w = target->target_pose.pose.orientation.w;
          //goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(target->theta);

                  
          ac.sendGoal(goal, 
                      boost::bind(&goalDoneCallback, _1, _2), 
                      boost::bind(&goalActiveCallback), boost::bind(&goalFeedbackCallback, _1));
      }
      // Spinning the loop and Callback
      ros::spinOnce();
      r.sleep();
    }

  ROS_INFO("Exiting Waypoint Navigation");
  return 0;
}
