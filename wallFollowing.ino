#include <Adafruit_RGBLCDShield.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "MySharpSensor.h"

#define YELLOW 0x3
#define SAFE_DISTANCE 5
#define K_P 0.6

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

float measuredFront = 0.0;
float measuredLeft = 0.0;
float measuredRight = 0.0;
float error = 0.0;
float inputSpeed = 0.0;
float realSpeed = 0.0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.setBacklight(0x3);
  lcd.setCursor(2, 1);

  initServo();
  setSpeedsIPS(0, 0);
  initDistanceSensors();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  uint8_t buttons = lcd.readButtons();

  if (buttons == BUTTON_SELECT){
    takeNewMeasurement(0);
    takeNewMeasurement(1);
    takeNewMeasurement(2);
    measuredLeft =  getCombinedDistance(0);
    measuredFront = getCombinedDistance(1);
    measuredRight = getCombinedDistance(2);
    error = measuredFront - SAFE_DISTANCE;
    inputSpeed = = error * K_P;
  
    if (inputSpeed >= maxSpeed()){
          realSpeed = maxSpeed();
        }

        else if ((inputSpeed < maxSpeed()) && (inputSpeed > ((-1) * maxSpeed()))){
            realSpeed = inputSpeed;
        }
        else if (inputSpeed <= ((-1) * maxSpeed())){
          realSpeed = (-1) * maxSpeed();  
        }

        setSpeedsIPS(realSpeed, realSpeed);
        if (error == 0)
        {
          setSpeedsvw(v, w); 
        }

        else if ((measuredLeft > SAFE_DISTANCE) && (measuredRight > SAFE_DISTANCE))
        {
          setSpeedsvw(v, -w);  
        }
   }
}
