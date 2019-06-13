



#ifndef __MY_ENCODERS__
#define __MY_ENCODERS__



//IF YOU WANT TO DECLARE VARIABLES VIEWABLE TO OTHER MODULE,
//DECLARE THEM HERE USING THE KEYWORD extern, then declare them in the .cpp

//this function sets the tick counts to 0
void resetCounts();

//this function should return the left and right tickcounts 
// since either the start of the program or the last
//call to the function resetCounts()
void getCounts(unsigned long counts[]);


//this function should return the instantaneous speeds of the wheels
//meassured in revolutions per second.
void getSpeeds(float speeds[]);
 
//this function should include whatever code necessary to initialize this module
void initEncoders();



#endif
