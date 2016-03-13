/*********************************************************************
ros-dumbobot-waypoint-navigation Node 
17 Floor 
Author : Theppasith Nisitsukcharoen
<theppasith@gmail.com , Theppasith.N@Student.chula.ac.th>
Department of Computer Engineering , Chulalongkorn University
*********************************************************************/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <nav_msgs/Odometry.h>
#include <vector>
#include <geometry_msgs/Pose2D.h>
#include <ros/package.h>
//File Reading Manipulator
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

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
  std::vector<std::string>   target_name;

//State Machine Implementation of Robot 
  class robotState{
    public:
      enum state{
      IDLE = 0,
      GOING = 1,
      WAITING = 2,
      BACKTOBASE = 3,
      SINGLERUN = 4,
    };
  };

  int robot_state;
  int startPoint_id;
  int endPoint_id;
  int choice = -1;
  move_base_msgs::MoveBaseGoal  startPoint;
  move_base_msgs::MoveBaseGoal  endPoint;
  move_base_msgs::MoveBaseGoal  currentPosition;

/////////////////////////////////////////////////////////////////////
///////////////   FUNCTION    ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////

void odometryCallback(const nav_msgs::Odometry::ConstPtr& msg){
  if(robot_state == robotState::IDLE){
    currentPosition.target_pose.pose.position.x    = msg->pose.pose.position.x;
    currentPosition.target_pose.pose.position.y    = msg->pose.pose.position.y;
    currentPosition.target_pose.pose.orientation.x = msg->pose.pose.orientation.x;
    currentPosition.target_pose.pose.orientation.y = msg->pose.pose.orientation.y;
    currentPosition.target_pose.pose.orientation.z = msg->pose.pose.orientation.z;
    currentPosition.target_pose.pose.orientation.w = msg->pose.pose.orientation.w;
    std::cout << currentPosition.target_pose.pose.position.x  <<" , " << currentPosition.target_pose.pose.position.y <<std::endl;
  }
}

int toint(std::string s) //The conversion function
{
    return atoi(s.c_str());
}


void displayWaypoints(){
  for(int i = 0 ; i < target_name.size() ; i++){
      std::cout <<"["<<i<<"] " << target_name[i] <<std::endl; 
    }
}


void read_waypoint_from(std::string filename){

   std::vector<std::string> tokenized;

   std::string path = ros::package::getPath("simple_navigation_goals")+ filename;
   std::ifstream inFile(path.c_str());
   std::string line;

   //First Value is Waypoint Counts 
   getline(inFile,line);
   int waypoint_count = toint(line);
   std::cout << waypoint_count <<std::endl;
   while(getline(inFile,line)){
    // New Line
      std::stringstream strstr(line);
      std::string word = "";

    // Ignore First Param (Place's Name)
      getline(strstr,word,',');
      target_name.push_back(word);
    // Gather Params
      while(getline(strstr,word,',')){
          tokenized.push_back(word);
      }
   }

   //Count All Parameters
   size_t counter = tokenized.size();
   std::cout << "Counter  : " << counter <<std::endl; 
   size_t point_amount = (size_t)(counter / 6.0);
   std::cout << "Div Count = " << point_amount << " ,  File Count = " << waypoint_count <<std::endl;


   std::vector<std::string>::iterator word_it;
   word_it = tokenized.begin();

   // Create move_base GOAL and Push into vector ! 
   for(int point_index = 0  ; point_index < counter ; point_index++){
      move_base_msgs::MoveBaseGoal newPoint;
      newPoint.target_pose.pose.position.x    = std::atof((word_it++)->c_str());
      newPoint.target_pose.pose.position.y    = std::atof((word_it++)->c_str());
      newPoint.target_pose.pose.orientation.x = std::atof((word_it++)->c_str());
      newPoint.target_pose.pose.orientation.y = std::atof((word_it++)->c_str());
      newPoint.target_pose.pose.orientation.z = std::atof((word_it++)->c_str());
      newPoint.target_pose.pose.orientation.w = std::atof((word_it++)->c_str());
      targets.push_back(newPoint);
      if(word_it == tokenized.end())break;
   }
}

void markCurrentLocation(){
         startPoint.target_pose.pose.position.x    = currentPosition.target_pose.pose.position.x;
         startPoint.target_pose.pose.position.y    = currentPosition.target_pose.pose.position.y;
         startPoint.target_pose.pose.orientation.x = currentPosition.target_pose.pose.orientation.x;
         startPoint.target_pose.pose.orientation.y = currentPosition.target_pose.pose.orientation.y;
         startPoint.target_pose.pose.orientation.z = currentPosition.target_pose.pose.orientation.z;
         startPoint.target_pose.pose.orientation.w = currentPosition.target_pose.pose.orientation.w;
}

void userInput(){
  choice = -1;
   // Loop for Waiting For User Input
  while(true){
    // Display Waypoint 
      displayWaypoints();

    // Ask for ID and wait user input
      std::cout << "Input Target Waypoints ID : " ;
      std::cin >>choice;

    // Desired For Returning ?
      bool delivery = false;
      int delivery_choice = 0;
      std::cout << "Delivery Mode ? (no = 0, yes = 1) : ";
      std::cin >> delivery_choice;
      delivery = (delivery_choice == 1)? true:false; 

    // If it is not violate the rules = Send Command Goal
    if(choice != -1 && choice<targets.size() && !delivery ){
      *target = targets[choice];
      // Commit as new Goal
      sendNewGoal = true;
      break;
    }else if(choice != -1 && choice<targets.size() && delivery ){
      // Delivery Mode
        robot_state = robotState::GOING;
        //Create the Starting point Location;
         //startPoint_id = 99; //From undefined Location
         markCurrentLocation();
         endPoint = targets[choice];
         *target = endPoint;
         // Commit as new goal
         sendNewGoal = true;
         break;
    }else{
      // Do nothing and Keep Looping
    }
  }



}

int waitfordelivery(){
  /*// Set the Timer to wait for 30 seconds
  ros::Time startTime = ros::Time::now();
  ros::Duration waitingDuration(10.0);
  while(true){
    ros::Time thisTime = ros::Time::now();
    if(thisTime - startTime > waitingDuration){
      return 1; //Timeout
    }

  }*/
  // Wait For Console Input 
    while(true/* && timeout_flag*/){
      robot_state = robotState::WAITING;
      std::cout << "AFTER YOU GOT THE PACKAGE " <<std::endl;
      std::cout << "PRESS ENTER TO CONTINUE" << std::endl;
      std::cin.ignore();
      std::cin.ignore();
      std::cout << "RETURNING TO BASE" <<std::endl;
      return 0; //user got parcel
    }
    return 1; // User Not Got Parcel
}

void goalDoneCallback_state(const actionlib::SimpleClientGoalState &state, 
  const move_base_msgs::MoveBaseResultConstPtr &result){

    if(state.state_ == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The goal was reached!");

    if(state.state_ == actionlib::SimpleClientGoalState::ABORTED)
        ROS_WARN("Failed to reach the goal...");

    
    std::cout << "Goal Finished Or Cancelled by Joy ::=>>>Ask For New Goal" << std::endl;
    
    //If It's just arrived
    if(robot_state == robotState::GOING)
    {
        //WAIT FOR PARCEL DELIVERY
      std::cout << "WAIT FOR ACCEPTANCE !" <<std::endl <<std::endl;
        int delivery_status = waitfordelivery();
        //After Delivering = Set Back to the First place
        robot_state = robotState::BACKTOBASE;
        *target = startPoint;
        sendNewGoal = true;
    }else if(robot_state == robotState::BACKTOBASE)
    {
        // IT IS JUST BACK FROM HELL - RELAX, MAN
        robot_state = robotState::IDLE;
        userInput();
    }
    
}


void goalDoneCallback(const actionlib::SimpleClientGoalState &state, 
  const move_base_msgs::MoveBaseResultConstPtr &result){

    if(state.state_ == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The goal was reached!");

    if(state.state_ == actionlib::SimpleClientGoalState::ABORTED)
        ROS_WARN("Failed to reach the goal...");

    std::cout << "Goal Finished Or Cancelled by Joy ::=>>>Ask For New Goal" << std::endl;
    choice = -1;
    while(true){
      std::cout << "Input Target Waypoints ID : " ;
      std::cin >>choice;

      //If it is not violate the rules
      if(choice != -1 && choice<targets.size() ){
        *target = targets[choice];
        sendNewGoal = true;
        break;
      }
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
   read_waypoint_from("/waypoints/waypoint.csv");
  //read_waypoint_from("/waypoints/waypoint_20.csv");
  
  target = targets.begin();
  ROS_INFO("Successfully Load waypoints from file!");

  // Callback polling Rate 
  ros::Rate r(30);
  bool online = true;
  robot_state = robotState::IDLE;

  // Wait for the action server to come up
  int tries = 0;
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up %d",tries+1);
    tries++;
    if(tries == 3){
      online = false;
      break;
    }
  }
  // Print Log to Console
  if(online)ROS_INFO("Navigation Waypoint Node Initialized !");
  else{
    ROS_INFO("Failed to Start Waypoint Node");
    return -1;
  }

  // Subscriber to Get Current position 
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/odom", 1000, odometryCallback);
  

  // Initialized !  
  userInput();

// Loop for Setting Goal and Navigate ! 
  sendNewGoal = true;
  // Start the Navigation Waypoint Loop
    while(ros::ok() && !finish ){

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
                      boost::bind(&goalDoneCallback_state, _1, _2), 
                      boost::bind(&goalActiveCallback), boost::bind(&goalFeedbackCallback, _1));
      }
      // Spinning the loop and Callback
      ros::spinOnce();
      r.sleep();
    }

  ROS_INFO("Exiting Waypoint Navigation");
  return 0;
}
