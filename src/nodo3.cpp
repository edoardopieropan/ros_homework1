/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 * 
 * Contributor: Edoardo Pieropan
 */

#include "ros/ros.h"
#include "homework1/personInfo.h"
#include "std_msgs/String.h"

//selecter will store the last letter received, default 'a'
char selected = 'a';

//The message received by Nodo1 will assign a value to all this varibles
std::string name;
std::string course;
int age;

//Callback Nodo1, will modify the person information
void chatterCallbackNodo1(const homework1::personInfo& msg)
{
  name = msg.name;
  course = msg.course;
  age = msg.age;
}

//Callback Nodo2, will display the chosen information
void chatterCallbackNodo2(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("New input received: [%s]", msg->data.c_str());

  char selectedBackup=selected; //To restore the old value if the letter is not a right one
  selected = msg->data.c_str()[0];

  //Can be done also w/ switch-case
  if(selected == 'a')
    ROS_INFO("Name: [%s], Age: [%i], Course: [%s]",name.c_str(), age, course.c_str());

  else if(selected == 'n')
    ROS_INFO("Name: [%s]", name.c_str());

  else if(selected == 'e')
    ROS_INFO("Age: [%i]", age);

  else if(selected == 'c')
    ROS_INFO("Course: [%s]",course.c_str());
  
  else{
    ROS_INFO("INVALID VALUE, you can choose between:\na (all)\nn (name)\ne (age)\nc (course)");
    selected = selectedBackup;
  }
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "nodo3");

  ros::NodeHandle n;

  //Subscribers
  ros::Subscriber sub_nodo1 = n.subscribe("pub_nodo1", 1000, chatterCallbackNodo1);
  ros::Subscriber sub_nodo2 = n.subscribe("pub_nodo2", 1000, chatterCallbackNodo2);

  ros::spin();
  return 0;
}
