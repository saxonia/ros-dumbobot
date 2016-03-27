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
#include <std_srvs/Empty.h>
#include <vector>
#include <geometry_msgs/Pose2D.h>
#include <ros/package.h>
//File Reading Manipulator
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <termios.h>

#include <tf/transform_listener.h>

//Timer 
  ros::Timer timer;
  bool createTimer;
//Costmap Clearing Service Client  
  ros::ServiceClient client;
  std_srvs::Empty clearer;

//Client Service of move_base 
  typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

//Global Variable
  bool sendNewGoal;
  bool finish;
  bool needmark;

//Waypoints 
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

  int targetId;
  int sequence[13] = {5,1,2,5,1,2,5,1,2,5,1,2,5};

/////////////////////////////////////////////////////////////////////
///////////////   FUNCTION    ///////////////////////////////////////
/////////////////////////////////////////////////////////////////////


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

    tf::TransformListener listener;  
    tf::StampedTransform transform;
    ros::Time now = ros::Time::now();
    try {
        listener.waitForTransform("map", "base_link", ros::Time(0), ros::Duration(10.0) );
        listener.lookupTransform("map", "base_link", ros::Time(0), transform);
    } catch (tf::TransformException ex) {
        ROS_ERROR("%s",ex.what());
    }

    startPoint.target_pose.pose.position.x    = transform.getOrigin().x();
    startPoint.target_pose.pose.position.y    = transform.getOrigin().y();
    startPoint.target_pose.pose.orientation.x = transform.getRotation().x();
    startPoint.target_pose.pose.orientation.y = transform.getRotation().y();
    startPoint.target_pose.pose.orientation.z = transform.getRotation().z();
    startPoint.target_pose.pose.orientation.w = transform.getRotation().w();

  std::cout << "RETURNING POINT MARKED : ";
  std::cout << startPoint.target_pose.pose.position.x <<","<<startPoint.target_pose.pose.position.y  <<std::endl;
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
        // Set Target According to Point of Interest
        *target = targets[sequence[targetId]];//*target = targets[choice];
        // Create new Goal
          robot_state = robotState::SINGLERUN;
          sendNewGoal = true;
        break;
    }else if(choice != -1 && choice<targets.size() && delivery ){
      // Delivery Mode      
         //Mark this location as startpoint
            markCurrentLocation();
         // Set Target According to Point of Interest
           endPoint = targets[choice];
           *target = endPoint;
         // Create new Goal 
           robot_state = robotState::GOING;
           sendNewGoal = true;
        break;
    }else{
      // Do nothing and Keep Looping
    }
  }
}
char getch()
{
    fd_set set;
    struct timeval timeout;
    int rv;
    char buff = 0;
    int len = 1;
    int filedesc = 0;
    FD_ZERO(&set);
    FD_SET(filedesc, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 1000;

    rv = select(filedesc + 1, &set, NULL, NULL, &timeout);

    struct termios old = {0};
    if (tcgetattr(filedesc, &old) < 0)
        ROS_ERROR("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(filedesc, TCSANOW, &old) < 0)
        ROS_ERROR("tcsetattr ICANON");

    if(rv == -1){
        ROS_ERROR("select");
    }else if(rv == 0){
        //ROS_INFO("no_key_pressed");
    }else{
        read(filedesc, &buff, len );
    }
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(filedesc, TCSADRAIN, &old) < 0)
        ROS_ERROR ("tcsetattr ~ICANON");
    return (buff);
}

// Wait FOR USER ACCEPTANCE !
int waitfordelivery(){
  // Wait Time 
  int waittime = 3; //seconds
  ros::Duration waitingDuration(waittime);
  ros::Time startTime = ros::Time::now();
  ros::Time thisTime = ros::Time::now();

  // Prompt User To Accept Parcel
  std::cout << "AFTER YOU GOT THE PACKAGE " <<std::endl;
  std::cout << "PRESS ANYKEY TO ACCEPT PARCEL" << std::endl;
  char keyin;
  int flag = -1;// Time Out

  //Wait For User Input Within Specific Timeout
  while(true){
    thisTime = ros::Time::now();
    if(thisTime - startTime > waitingDuration)break;
    keyin = getch();
    if((int)keyin != 0){
      flag = 1;
      break;
    }
  }

  // Prompt Result Delivering Status
  if(flag == -1)std::cout <<"[" << flag <<"]TIME OUT => RETURNING TO BASE WITH PARCEL !" << std::endl;
  if(flag == 1)std::cout <<"[" << flag <<"]PARCEL ACCEPTED ! =>RETURNING TO BASE!" << std::endl;
  std::cout << "FLAG = " << flag << std::endl;
  return flag;

}

void nextTarget(){
  targetId++;
  if(targetId >=14){
   finish = true; 
  }
}

void timerCallback(const ros::TimerEvent &event){
  /*DO SOMETHING 

  

  AFTER TIMER FINISH HERE*/

  //Prompt :D
  std::cout << "@@@@@@@@Timer has just finished" <<std::endl;
  client.call(clearer);
  // Clear the Costmap 


  // This Timer is finish , request to create it again;
    createTimer = true;
    return;
}

void goalDoneCallback_state(const actionlib::SimpleClientGoalState &state, 
  const move_base_msgs::MoveBaseResultConstPtr &result){

    if(state.state_ == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The goal was reached!");

    if(state.state_ == actionlib::SimpleClientGoalState::ABORTED)
        ROS_WARN("Failed to reach the goal...");
    
    std::cout << "Goal Finished Or Cancelled by Joy ::=>>>Ask For New Goal" << std::endl;
    
    // If It's just arrived
    if(robot_state == robotState::GOING){

        // WAIT FOR PARCEL DELIVERY
          std::cout << "WAIT FOR ACCEPTANCE !" <<std::endl <<std::endl;
          int delivery_status = waitfordelivery();

        // After Delivering = Set Back to the First place
          robot_state = robotState::BACKTOBASE;
          *target = startPoint;
          std::cout << "GOING TO : ";
          std::cout << startPoint.target_pose.pose.position.x <<","<<startPoint.target_pose.pose.position.y  <<std::endl;
          sendNewGoal = true;

    }else if(robot_state == robotState::BACKTOBASE){

        // IT IS JUST BACK FROM HELL - RELAX, MAN
          robot_state = robotState::IDLE;
        // Ask User For the Next Target
           userInput();

    }else if(robot_state == robotState::SINGLERUN){

        // SINGLE POINT APPROACH
          robot_state = robotState::IDLE;
        //Wait Just a while
          waitfordelivery();
        // Ask User For the Next Target  
          //userInput();
          nextTarget();
           *target = targets[sequence[targetId]];
          sendNewGoal = true;
          robot_state = robotState::SINGLERUN;
    }
}

void goalActiveCallback(){
  //ROS_INFO("Goal active! Hurray!");
}


void goalFeedbackCallback(const move_base_msgs::MoveBaseFeedbackConstPtr &feedback){
  //ROS_INFO("Getting feedback! How cool is that?");
}



int main(int argc, char** argv){

  // Create Node 
    ros::init(argc, argv, "simple_navigation_goals");

  // Marking Current Location (For First Time Usage)
    markCurrentLocation();

  // Tell the action client that we want to spin a thread by default
    MoveBaseClient ac("move_base", true);

  // Read waypoint from file to vector
    read_waypoint_from("/waypoints/waypoint.csv");
     //read_waypoint_from("/waypoints/waypoint_20.csv");
    ROS_INFO("Successfully Load waypoints from file!");

  // Point The iterator to the beginning of the sequence
    target = targets.begin();
  
  // Request To Create timer
    createTimer = true;

  // Callback polling Rate 
    ros::Rate r(30);

  // Flag to Check Move-base Server
    bool online = true;

  // Initialize ROBOT :)
    robot_state = robotState::IDLE;

  // Flag For Marking Base Location (Request Current Location Flag)
    needmark = false;

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

  // Prompt Server Status 
  if(online)ROS_INFO("Navigation Waypoint Node Initialized !");
  else{
    ROS_INFO("Failed to Start Waypoint Node");
    return -1;
  }

  // Subscriber to Get Current position 
    ros::NodeHandle n;

  // Subscribe to Map Clearing Service 
    client = n.serviceClient<std_srvs::Empty>("/move_base_node/clear_costmaps");

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

          // Send Goal to Navigation Stack
          ac.sendGoal(goal, 
                      boost::bind(&goalDoneCallback_state, _1, _2), 
                      boost::bind(&goalActiveCallback), boost::bind(&goalFeedbackCallback, _1));

      }

      //Check if the timer should be create.
      if(createTimer){

        timer = n.createTimer(ros::Duration(10), timerCallback);

        //We Don't want to create timer anymore
        createTimer = false;
      }

      // Spinning the loop and Callback
      ros::spinOnce();
      r.sleep();
    }

  ROS_INFO("Exiting Waypoint Navigation");
  return 0;
}
