
#include "MySharpSensor.h"
#include "Arduino.h"

#define SLEFT 0
#define SSFRONT 1
#define SRIGHT 2
#define SLONG  3

#define N 19

namespace{
    int leftR[N + 1];
    int shortFrontR[N + 1];
    int rightR[N + 1];
    int longFrontR[N + 1];
    int leftIndex = 0;
    int rightIndex = 0;
    int shortFrontIndex = 0;
    int longFrontIndex = 0;
}



float shortToInches(int value){
    float voltage = (float)(value * 0.00489);
    
    if (voltage > 3.04)
    {
        return 1.2;
    }
    
    else if ((voltage > 3) && (voltage <= 3.04))
    {
        return (16.14 - 4.921 * voltage);
    }
    
    else if ((voltage > 2.73) && (voltage <= 3))
    {
        return (3.565 - 0.729 * voltage);
    }
    
    else if ((voltage > 2.34) && (voltage <= 2.73))
    {
        return (4.197 - 0.96 * voltage);
    }
    
    else if ((voltage > 2.01) && (voltage <= 2.34))
    {
        return (4.76 - 1.193 * voltage);
    }
    
    else if ((voltage > 1.78) && (voltage <= 2.01))
    {
        return (5.803 - 1.71 * voltage);
    }
    
    else if ((voltage > 1.57) && (voltage <= 1.78))
    {
        return (6.093 - 1.875 * voltage);
    }
    
    else if ((voltage > 1.4) && (voltage <= 1.57))
    {
        return (6.785 - 2.316 * voltage);
    }
 
    else if ((voltage > 1.27) && (voltage <= 1.4))
    {
        return (7.783 - 3.028 * voltage);
    }
    
    else if ((voltage > 1.06) && (voltage <= 1.27))
    {
        return (8.699 - 3.75 * voltage);
    }
    
    else if ((voltage > 0.93) && (voltage <= 1.06))
    {
        return (11.145 - 6.057 * voltage);
    }
    
    else if ((voltage > 0.81) && (voltage <= 0.93))
    {
        return (11.614 - 6.56 * voltage);
    }
    
    else if ((voltage > 0.74) && (voltage <= 0.81))
    {
        return (15.41 - 11.25 * voltage);
    }
    
    else if ((voltage > 0.65) && (voltage <= 0.74))
    {
        return (13.559 - 8.749 * voltage);
    }
    
    else if ((voltage > 0.53) && (voltage <= 0.65))
    {
        return (18.537 - 16.404 * voltage);
    }
    
    else if ((voltage > 0.42) && (voltage <= 0.53))
    {
        return (19.327 - 17.895 * voltage);
    }
    
    else if ((voltage > 0.38) && (voltage <=0.42))
    {
        return (32.48 - 49.213 * voltage);
    }
    
    else if ((voltage > 0.31) && (voltage <=0.38))
    {
        return (24.466 - 28.121 * voltage);
    }
}



float longToInches(int value){
    float voltage = (float)(value * 0.00489);
    
    if (voltage > 2.75)
        return 0;
    
    else if ((voltage > 2.51) && (voltage <= 2.75))
    {
        return (28.461 - 8.202 * voltage);
    }
    
    else if ((voltage > 2) && (voltage <= 2.51))
    {
        return (27.25 - 7.72 * voltage);
    }
    
    else if ((voltage > 1.5) && (voltage <= 2))
    {
        return (27.559 - 7.874 * voltage);
    }
    
    else if ((voltage > 1.25) && (voltage <= 1.5))
    {
        return (39.37 - 15.748 * voltage);
    }
    
    else if ((voltage > 1.05) && (voltage <= 1.25))
    {
        return (44.291 - 19.685 * voltage);
    }
    
    else if ((voltage > 0.9) && (voltage <= 1.05))
    {
        return (51.181 - 26.247 * voltage);
    }
    
    else if ((voltage > 0.8) && (voltage <= 0.9))
    {
        return (62.992 - 39.37 * voltage);
    }
    
    else if ((voltage > 0.7) && (voltage <= 0.8))
    {
        return (62.992 - 39.37 * voltage);
    }
    
    else if ((voltage > 0.65) && (voltage <= 0.7))
    {
        return (90.551 - 78.74 * voltage);
    }
    
    else if ((voltage > 0.6) && (voltage <= 0.65))
    {
        return (90.551 - 78.74 * voltage);
    }
    
    else if ((voltage > 0.55) && (voltage <= 0.6))
    {
        return (90.551 - 78.74 * voltage);
    }
    
    else if ((voltage > 0.5) && (voltage <= 0.55))
    {
        return (90.551 - 78.74 * voltage);
    }
    
    else if ((voltage > 0.46) && (voltage <= 0.5))
    {
        return (90.551 - 78.74 * voltage);
    }
    
    else
        return 60;
}



int takeNewMeasurement(int sensor)
{
    int rawValue = analogRead(sensor);
    
    switch (sensor) {
        case SLEFT: {
            leftR[leftIndex] = rawValue;
            leftIndex ++;
            if (leftIndex == N + 1){
                leftIndex = 0;
            }
        }
        
        case SSFRONT: {
            shortFrontR[shortFrontIndex] = rawValue;
            shortFrontIndex ++;
            if (shortFrontIndex == N + 1){
                shortFrontIndex = 0;
            }
        }
            
        case SRIGHT: {
            rightR[rightIndex] = rawValue;
            rightIndex ++;
            if (rightIndex == N + 1){
                rightIndex = 0;
            }
        }
            
        case SLONG: {
            longFrontR[leftIndex] = rawValue;
            longFrontIndex ++;
            if (longFrontIndex == N + 1){
                longFrontIndex = 0;
            }
        }
    }
    return rawValue;
}



float getCombinedDistance(int sensor){
    int totalRaw = 0;
    int averageRaw = 0;
    
    switch (sensor) {
        case SLEFT: {
            for (int i = 0; i <= N; i ++){
                totalRaw += leftR[i];
            }
            averageRaw = totalRaw / (N + 1);
            return shortToInches(averageRaw);
        }
            
        case SSFRONT: {
            for (int i = 0; i <= N; i ++){
                totalRaw += shortFrontR[i];
            }
            averageRaw = totalRaw / (N + 1);
            return shortToInches(averageRaw);
        }
            
        case SRIGHT: {
            for (int i = 0; i <= N; i ++){
                totalRaw += rightR[i];
            }
            averageRaw = totalRaw / (N + 1);
            return shortToInches(averageRaw);
        }
            
        case SLONG: {
            for (int i = 0; i <= N; i ++){
                totalRaw += longFrontR[i];
            }
            averageRaw = totalRaw / (N + 1);
            return longToInches(averageRaw);
        }
    }
}

#define SLEFT 0
#define SSFRONT 1
#define SRIGHT 2
#define SLONG  3

void initDistanceSensors(){
    for (int sensor = 0; sensor <= 3; sensor ++){
        for (int i = 0; i <= N; i ++){
            takeNewMeasurement(sensor);
        }
    }
}
