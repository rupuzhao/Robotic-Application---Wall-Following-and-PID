


#ifndef __MY_SHARP_SENSOR__
#define __MY_SHARP_SENSOR__



//this function takes as input the value obtained by a short distance sensor,
//and it should return its respective value in inches
float shortToInches(int value);

//this function takes as input the value obtained by the long distance sensor,
//and it should return its respective value in inches
float longToInches(int value);


//the following two functions are meant to break up the process of taking multiple measurements and filtering to reduce noise

//this function should read and store exactly one new measurement taken with the sensor given by the parameter 'sensor'
//it might be useful to know what's a circular buffer
int takeNewMeasurement(int sensor);


//this function should apply a filter the last N measurement taken with the sensor 'sensor' and return the result.
//You are free to chose the value of N and combination method
float getCombinedDistance(int sensor);


//all code to initialize the module should be added in this function:
void initDistanceSensors();

#endif
