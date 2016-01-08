/*********************************************************************
Dumbobot - Controller
Author : Theppasith Nisitsukcharoen
<theppasith@gmail.com , Theppasith.N@Student.chula.ac.th>
Department of Computer Engineering , Chulalongkorn University
*********************************************************************/

#include <serial/serial.h>
#include "ros_dumbobot/controller.h"

#include <boost/bind.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <unistd.h>
#include <iostream>
#include <sstream>

#ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif

#define DUMBO_MAX_SPEED 150
#define DUMBO_MIN_SPEED 50


namespace dumbo{

Controller::Controller(const char *port, int baud)
  : nh_("~"),
  port_(port),
  baud_(baud),
  connected_(false),
  receiving_script_messages_(false),
  version_(""),
  serial_(NULL)

{
  //pub_status_ = nh_.advertise<roboteq_msgs::Status>("status", 1);
}

Controller::~Controller() {
  send_stop();
}

char calculateChecksum(unsigned char *buffer , unsigned int buffer_size){
    int16_t sum =0;
    for(unsigned int i = 2 ; i < buffer_size ; i++ ){
        sum += (int)buffer[i];
    }
    return ((char)(sum & 0xFF)^0xFF);
}


// Create Connection to DUMBOBOT CONTROLLER
void Controller::connect() {
  if (!serial_) serial_ = new serial::Serial();
  serial::Timeout to(serial::Timeout::simpleTimeout(1000));
  serial_->setTimeout(to);
  serial_->setPort(port_);
  serial_->setBaudrate(baud_);

  for (int tries = 0; tries < 5; tries++) {
    try {
      serial_->open();
    } catch (serial::IOException) {
      std::cout << "Unable to open port " << std::endl;
    }

    if (serial_->isOpen()) {
      std::cout << "Successfully Connected to DUMBOBOT" <<std::endl;
      connected_ = true;
      return;
    } else {
      connected_ = false;
      ROS_INFO("Bad Connection with serial port Error %s",port_);
    }
  }
  ROS_INFO("Dumbo controller not responding.");
}



void Controller::read(){
  serial_->read(buff,BUFFERSIZE);
}
int Controller::read_drive_command(){
  int readed = serial_->read(buff,12);
  std::cout << "readed = " << readed << "bytes" <<std::endl;
  return readed;
}

int Controller::ser_send_avail(){
  int read = serial_->available();
  return read;
} 

void Controller::driveTutor(int left_speed , int left_dir , int right_speed , int right_dir)
{

  // Limit velocity
  int16_t leftSpeed  = MAX(left_speed, DUMBO_MIN_SPEED);  //MINIMUM at 50
          leftSpeed  = MIN(leftSpeed, DUMBO_MAX_SPEED);  //MAXIMUM at 100
  
  int16_t rightSpeed  = MAX(right_speed, DUMBO_MIN_SPEED);  //MINIMUM at 50
          rightSpeed  = MIN(rightSpeed, DUMBO_MAX_SPEED);  //MAXIMUM at 100

  //Cast int to int16_t for Serial Buffer
  int16_t leftDirection,rightDirection; //1 FORWARD  2 BACKWARD
  leftDirection = left_dir;
  rightDirection = right_dir;
  //Driving Command Protocol to Arduino Mega
  // Compose Driving Command
    unsigned char cmd_buffer[11];
  // Headers
    cmd_buffer[0] = (char)0xFF; //255
    cmd_buffer[1] = (char)0xFF; //255
    cmd_buffer[2] = (char)0x01; //001
  // counter
    cmd_buffer[3] = (char)0x07; //007
  // Error Bit
    cmd_buffer[4] = (char)0x03; //003
  // Starting Address
    cmd_buffer[5] = (char)0x14; // ('1' x 16 ) + ('4') = 020
  // Direction        V - Right Motor
    cmd_buffer[6] = (char)(rightDirection & 0xFF);
  // Velocity Amount    V - Right Motor
    cmd_buffer[7] = (char)(rightSpeed & 0xFF);
  // Direction        V - Left Motor
    cmd_buffer[8] = (char)(leftDirection & 0xFF);
  // Velocity Amount    V - Left Motor
    cmd_buffer[9] = (char)(leftSpeed & 0xFF);
  // CHECKSUM
    cmd_buffer[10] = calculateChecksum(cmd_buffer,10);

    // Send Packages
    serial_->write(cmd_buffer,11);

}




void Controller::driveDirect(double linear , double angular)
{

  /*
 * USE LINEAR AND ANGULAR SPEED TO DRIVE 
 * FOR GMAPPING NAV BY RVIZ
 */


}


void Controller::send_forward(int speed)
{
  // Limit velocity
  int16_t sent_speed_int  = MAX(speed, DUMBO_MIN_SPEED);  //MINIMUM at 50
      sent_speed_int  = MIN(sent_speed_int, DUMBO_MAX_SPEED);  //MAXIMUM at 100
    std::cout << "FORWARD COMMAND WITH SPEED (BOUNDED) = " << sent_speed_int << std::endl;
  //Driving Command Protocol to Arduino Mega
  // Compose Driving Command
    unsigned char cmd_buffer[11];
  // Headers
    cmd_buffer[0] = (char)0xFF; //255
    cmd_buffer[1] = (char)0xFF; //255
    cmd_buffer[2] = (char)0x01; //001
  // counter
    cmd_buffer[3] = (char)0x07; //007
  // Error Bit
    cmd_buffer[4] = (char)0x03; //003
  // Starting Address
    cmd_buffer[5] = (char)0x14; // ('1' x 16 ) + ('4') = 020
  // Direction        V - Right Motor
    cmd_buffer[6] = (char)0x01;
  // Velocity Amount    V - Right Motor
    cmd_buffer[7] = (char)(sent_speed_int& 0xFF);
  // Direction        V - Left Motor
    cmd_buffer[8] = (char)0x01;
  // Velocity Amount    V - Left Motor
    cmd_buffer[9] = (char)(sent_speed_int& 0xFF);
  // CHECKSUM
    cmd_buffer[10] = calculateChecksum(cmd_buffer,10);

    // Send Packages
    serial_->write(cmd_buffer,11);

}

void Controller::send_stop(){

//255 255 001 007 003 020 000 255 000 255 226
      // Compose Driving Command
    unsigned char cmd_buffer[11];
  // Headers
    cmd_buffer[0] = (char)0xFF; //255
    cmd_buffer[1] = (char)0xFF; //255
    cmd_buffer[2] = (char)0x01; //001
  // counter
    cmd_buffer[3] = (char)0x07; //007
  // Error Bit
    cmd_buffer[4] = (char)0x03; //003
  // Starting Address
    cmd_buffer[5] = (char)0x14; // ('1' x 16 ) + ('4') = 020
  // Direction        V - Right Motor
    cmd_buffer[6] = (char)0x00;
  // Velocity Amount    V - Right Motor
    cmd_buffer[7] = (char)0xFF;
  // Direction        V - Left Motor
    cmd_buffer[8] = (char)0x00;
  // Velocity Amount    V - Left Motor
    cmd_buffer[9] = (char)0xFF;
  // CHECKSUM
    cmd_buffer[10] = (char)0xE2;

    // Send Packages
    serial_->write(cmd_buffer,11);
}


void Controller::openSerialPort(std::string port) {
    try{
        ser.setPort(port);
        ser.setBaudrate(9600);
        serial::Timeout to = serial::Timeout::simpleTimeout(1000);
        ser.setTimeout(to);
        ser.open();
        connected_ = true;
        //send_stop();
    }catch (serial::IOException& e){
        std::cout << "Unable to open port " << std::endl;
        connected_ = false;
    }
}

} //namespace dumbo

