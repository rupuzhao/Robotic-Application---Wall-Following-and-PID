


#ifndef __MY_SERVOS__
#define __MY_SERVOS__



//NOTE: you are allowed to modify this file as long as the functions
//implement the requested functionality

//IF YOU WANT TO DECLARE VARIABLES VIEWABLE TO OTHER MODULES,
//DECLARE THEM HERE USING THE KEYWORD extern, then declare them in the .cpp


//this function should set the left and right speeds of the wheel
//when both inputs are positive the robot should move forward
//when both inputs are negative the robot should move backward
//microsLeft should encode the left wheel velocity and viceversa
void setSpeeds(int microsLeft, int microsRight);

void initServo();


//same as the function setSpeeds, but the inputs now indicate 
//the revolutions per secont (rps) at which each wheel should spin
void setSpeedsRPS(float rpsLeft, float rpsRight);



//same as the function setSpeeds, but the inputs now indicate 
//the inches per second (ips) at which each wheel should spin
void setSpeedsIPS(float ipsLeft, float ipsRight);


//this function is meant for doing whatever necessary for the 
//functions 'setSpeedsIPS' and 'setSpeedsRPS' to work properly
void calibrate();

float leftMax();



float rightMax();


float maxSpeed();


void printCalibration();



bool isPossibleVW(float v, float w);


//this function should make the robot move with a linear speed of v 
//measured in inches per second, and an angular speed of w
//in rads per second. Positive ws should indicate a counterclockwise spin.
void setSpeedsvw(float v, float w);



#endif 
