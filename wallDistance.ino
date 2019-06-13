#include <Adafruit_RGBLCDShield.h>
#include "MyEncoders.h"
#include "MyServos.h"
#include "MySharpSensor.h"

#define YELLOW 0x3
#define DESIRED_DISTANCE 5
#define K_P 5.0

Adafruit_RGBLCDShield lcd = Adafruit_RGBLCDShield();

const int shortSensor = A0;
float measuredDistance = 0.0;
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
        
        int raw = takeNewMeasurement(1);
        measuredDistance = getCombinedDistance(1);
        lcd.setCursor(2, 1);
        lcd.print("           ");
        lcd.setCursor(2, 1);
        lcd.print(raw);
        lcd.setCursor(7, 1);
        lcd.print(measuredDistance);
        Serial.println(measuredDistance);
        error = measuredDistance - DESIRED_DISTANCE;
        inputSpeed = error * K_P;
        if (inputSpeed >= maxSpeed()){
          realSpeed = maxSpeed();
        }

        else if (  (inputSpeed < maxSpeed() ) && ( inputSpeed > -maxSpeed() )  ){
            realSpeed = inputSpeed;
        }
        else if (inputSpeed <= - maxSpeed()){
          realSpeed = -maxSpeed();  
        }

        setSpeedsIPS(realSpeed, realSpeed);

        delay(30);
}
