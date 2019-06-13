//implement in this document the functions from MyServos.h
#include "MyServos.h"
#include <Servo.h>
#include "MyEncoders.h"
#include "Arduino.h"
#define N 41


namespace {
  //this is a nameless namespace
  //put here variables only viewable to this module
  
  Servo leftServo;
  Servo rightServo;
  
  float leftCaliRPS[N] = {-0.70, -0.70, -0.70, -0.70, -0.72, -0.70, -0.72, -0.70, -0.70, -0.69, -0.67, -0.66, -0.63, -0.61, -0.56, -0.48, -0.39, -0.28, -0.17, -0.08, 0.00, 0.03, 0.12, 0.25, 0.34, 0.44, 0.50, 0.58, 0.63, 0.64, 0.66, 0.67, 0.69, 0.69, 0.70, 0.70, 0.72, 0.70, 0.70, 0.72, 0.70
};
  float rightCaliRPS[N] = {-0.70, -0.70, -0.70, -0.70, -0.70, -0.70, -0.70, -0.70, -0.69, -0.69, -0.67, -0.66, -0.63, -0.61, -0.56, -0.48, -0.39, -0.30, -0.19, -0.08, 0.00, 0.08, 0.17, 0.28, 0.37, 0.48, 0.55, 0.61, 0.64, 0.67, 0.67, 0.69, 0.69, 0.70, 0.70, 0.70, 0.70, 0.70, 0.70, 0.70, 0.70
};
}



//NOTE: you are allowed to modify this file as long as the functions
//implement the requested functionality

//IF YOU WANT TO DECLARE VARIABLES VIEWABLE TO OTHER MODULES,
//DECLARE THEM HERE USING THE KEYWORD extern, then declare them in the .cpp


//this function should set the left and right speeds of the wheel
//when both inputs are positive the robot should move forward
//when both inputs are negative the robot should move backward
//microsLeft should encode the left wheel velocity and viceversa
void setSpeeds(int microsLeft, int microsRight){
    leftServo.writeMicroseconds(1500 + microsLeft);
    rightServo.writeMicroseconds(1500 - microsRight);
}

void initServo(){
    leftServo.attach(2);
    rightServo.attach(3);
}


//same as the function setSpeeds, but the inputs now indicate 
//the revolutions per secont (rps) at which each wheel should spin
void setSpeedsRPS(float rpsLeft, float rpsRight){
    float leftSpeed;
    float rightSpeed;
    
    //angular speed of left wheel
    
    if (rpsLeft <= leftCaliRPS[0]){
        leftSpeed = -200;
    }
    else if (rpsLeft >= leftCaliRPS[40]){
        leftSpeed = 200;
    }
    else {
        for (int i = 1; i < N; i ++){
            if (rpsLeft == leftCaliRPS[i]){
                leftSpeed = -200 + 10 * i;
            }
            else if (rpsLeft > leftCaliRPS[i - 1] && rpsLeft < leftCaliRPS[i]){
                leftSpeed = -200 + 10 * (i - 1) + 10 * ((rpsLeft - leftCaliRPS[i - 1]) / (leftCaliRPS[i] - leftCaliRPS[i - 1]));
            }
        }
    }
    
    //angular speed of right wheel
    if (rpsRight <= rightCaliRPS[0]){
        rightSpeed = -200;
    }
    else if (rpsRight >= rightCaliRPS[40]){
        rightSpeed = 200;
    }
    else {
      for (int j = 1; j < N; j ++){
          if (rpsRight == rightCaliRPS[j]){
              rightSpeed = -200 + 10 * j;
//              Serial.print("c1 ");
//              Serial.print(j);
//              Serial.print("\t");
//              Serial.print(rpsRight);
//              Serial.print("\t");
//              Serial.println(rightCaliRPS[j]);
          }
          else if (rpsRight > rightCaliRPS[j - 1] && rpsRight < rightCaliRPS[j]){
              rightSpeed = -200 + 10 * (j - 1) + 10 * ((rpsRight - rightCaliRPS[j - 1]) / (rightCaliRPS[j] - rightCaliRPS[j - 1]));

//              Serial.print("c2 ");
//              Serial.print(j);
//              Serial.print("\t");
//              Serial.print(rpsRight);
//              Serial.print("\t");
//              Serial.println(rightCaliRPS[j]);
          }
    }
  } 
    setSpeeds(leftSpeed, rightSpeed);
}


//same as the function setSpeeds, but the inputs now indicate 
//the inches per second (ips) at which each wheel should spin
void setSpeedsIPS(float ipsLeft, float ipsRight){
    float d = 2.61;
    float leftSpeed = ipsLeft / (3.14 * d);
    float rightSpeed = ipsRight / (3.14 * d);

    setSpeedsRPS(leftSpeed, rightSpeed);
}


void printArrayCalibration(){
    Serial.print(leftCaliRPS[0]);
    for (int i = 1; i < N; i ++){
        Serial.print(", ");
        Serial.print(leftCaliRPS[i]);
    }
    Serial.println();
    
    
    Serial.print(rightCaliRPS[0]);
    for (int i = 1; i < N; i ++){
        Serial.print(", ");
        Serial.print(rightCaliRPS[i]);
    }
    Serial.println();
}

//this function is meant for doing whatever necessary for the 
//functions 'setSpeedsIPS' and 'setSpeedsRPS' to work properly
#define CALITIME 2
void calibrate(){
    for (int i = 0; i < N; i ++){
        int us = -200 + i * 10;
        setSpeeds(us,us);
        delay(100);
        resetCounts();
        delay(CALITIME * 1000);
        unsigned long mcounts[2];
        getCounts(mcounts);
        
        //rotations = counted holes / total holes
        
        leftCaliRPS[i] = us > 0 ?  (float)(mcounts[0]) / (32.0 * CALITIME)  : -(float)(mcounts[0]) / (32.0 * CALITIME);
        rightCaliRPS[i] = us > 0 ? (float)(mcounts[1]) / (32.0 * CALITIME) : -(float)(mcounts[1]) / (32.0 * CALITIME);
    }
    setSpeeds(0, 0);
    Serial.println("Done Calibration: ");
    printArrayCalibration();
}

void printCalibration(){
    for (int i = 0; i < N; i ++){
        int us = -200 + i * 10;
        
        Serial.print(us);
        Serial.print('\t');
        Serial.println(rightCaliRPS[i]);
    }
}



//this function should make the robot move with a linear speed of v 
//measured in inches per second, and an angular speed of w
//in rads per second. Positive ws should indicate a counterclockwise spin.
void setSpeedsvw(float v, float w){
    float leftSpeed = v - w * (3.95 / 2);
    float rightSpeed = v + w * (3.95 / 2);  
    
    
    setSpeedsIPS(leftSpeed, rightSpeed);
}


float leftMax(){
    return (2.61 * 3.14 * leftCaliRPS[40]);
}



float rightMax(){
    return (2.61 * 3.14 * rightCaliRPS[40]); 
}


float maxSpeed(){
  if (leftCaliRPS[40] <= rightCaliRPS[40]){
    return (2.61 * 3.14 * leftCaliRPS[40]);
  }

  else if (leftCaliRPS[40] > rightCaliRPS[40]){
    return (2.61 * 3.14 * rightCaliRPS[40]);  
  }
}



bool isPossibleVW(float v, float w){
    float leftSpeed = v - w * (3.95 / 2);
    float rightSpeed = v + w * (3.95 / 2);

    return (abs(leftSpeed) < leftMax()) && (abs(rightSpeed) < rightMax());
}

 


