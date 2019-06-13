//implement in this document the functions from MyEncoders.h
#include "MyEncoders.h"
#include <PinChangeInt.h>
#include "Arduino.h"

namespace {
  //this is a nameless namespace
  //put here variables only viewable to this module
  unsigned long leftTickCounts;
  unsigned long rightTickCounts;
  unsigned long leftTime1;
  unsigned long rightTime1;
  unsigned long leftTime2;
  unsigned long rightTime2;

}



//this function sets the tick counts to 0
void resetCounts(){
    noInterrupts();
    leftTickCounts = 0;
    rightTickCounts = 0;
   interrupts();
}

//this function should return the left and right tickcounts 
// since either the start of the program or the last
//call to the function resetCounts()
void getCounts(unsigned long counts[]){
    noInterrupts();
    counts[0] = leftTickCounts;
    counts[1] = rightTickCounts;
    interrupts();
}

void leftInterrupt(){
    leftTickCounts++;
    leftTime1 = leftTime2;
    leftTime2 = millis();
}

void rightInterrupt(){
    rightTickCounts++;
    rightTime1 = rightTime2;
    rightTime2 = millis();
}

//this function should return the instantaneous speeds of the wheels
//meassured in revolutions per second.
void getSpeeds(float speeds[]){
    speeds[0] = (1.0 / 32.0) / (leftTime2 - leftTime1) * 1000;
    speeds[1] = (1.0 / 32.0) / (rightTime2 - rightTime1) * 1000;
}

//this function should include whatever code necessary to initialize this module
void initEncoders(){
    resetCounts();
    pinMode(10, INPUT_PULLUP);
    pinMode(11, INPUT_PULLUP);
    PCintPort::attachInterrupt(10,&leftInterrupt,FALLING);
    PCintPort::attachInterrupt(11,&rightInterrupt,RISING);
}


