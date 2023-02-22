#include "Ultrasonic.h"
 
Ultrasonic ultrasonic(5);
void setup()
{
    Serial.begin(19200);
}
void loop()
{
    float RangeInCentimeters;
    float actualHeight;
    float fixedHeight = 201; //change this value with respect to the calib 
 
    //Serial.println("Height is: ");
   
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); 
    actualHeight = fixedHeight - RangeInCentimeters;// change fixedHeight according to the height from the base during calibration
    if(actualHeight >= 0 || actualHeight <= 201)
    {
    Serial.print(abs(actualHeight));//0~400cm
    Serial.println(" cm");
    delay(50);
    } 
    else
    {
    Serial.print(abs(0));//0~400cm
    Serial.println(" cm");
    }
}

