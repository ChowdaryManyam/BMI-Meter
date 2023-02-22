#include "BluetoothSerial.h" 
#include "HX711.h"

#define calibration_factor -20369.60 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define LOADCELL_DOUT_PIN  14
#define LOADCELL_SCK_PIN  12

HX711 scale;

#include "Ultrasonic.h"
 
Ultrasonic ultrasonic(5);

// init Class:
BluetoothSerial ESP_BT; 


// Parameters for Bluetooth interface
String readString;

void setup()
 {
  Serial.begin(19200);
  ESP_BT.begin("Growth Meter_Proto"); //Name of your Bluetooth interface -> will show up on your phone


  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  //Serial.println("Readings:");

}

void loop() 
{

    float RangeInCentimeters;
    float actualHeight;
    float fixedHeight = 201; //change this value with respect to the calib 
 
 
    RangeInCentimeters = ultrasonic.MeasureInCentimeters(); 
    actualHeight = fixedHeight - RangeInCentimeters;// change fixedHeight according to the height from the base during calibration
    delay(50);



 while(ESP_BT.available()) 
  {
    //delay(50);
    char c = ESP_BT.read(); //Read what we receive 
    readString+=c;
   if(readString.length()>0)
    {
    //Serial.println(readString);
    if (readString =="S")
    {     // send data
      Serial.println(readString);//print S
      if(actualHeight >= 0 || actualHeight <= 201)
      {
      Serial.println(abs(actualHeight));//0~400cm
      ESP_BT.print("Height in Cm is:");
      ESP_BT.println(abs(actualHeight));
      }
      else
      {
       Serial.println(abs(0)); //Serial print
       ESP_BT.print("Height in Cm is:"); //BT print
       ESP_BT.print(abs(0));//0~400cm //BT print
       Serial.print(" cm");
      }

      ESP_BT.print("Weight in Kg is:");//BT print
      ESP_BT.println(abs(scale.get_units()),1);//BT print
      Serial.println(abs(scale.get_units()),1);//Serial print
      //ESP_BT.write(scale.get_units()); 
      
    }
    readString="";
    }   
  }
}//end of void loop

