#include <Arduino.h>
// Ingo Lohs, works with Particle Photon v0.7.0-rc.1
// MQ-7 Carbon Monoxide Sensor: It is sensitive to gases like Alcohol (hand sanitizer), Butane (a lighter) and Difluoroethane (compressed "air" duster), among other gasses. 
// 31.08.2017, v1.0
// datasheet found here: http://cvrr.ucsd.edu/ece156/ECE156Sensors/Carbon_Monoxide.pdf

// MQ-7 wiring
#define analogMQ7 A0      // Signal 
int MQ7sensorValue = 0;   // value read from the sensor

// *********************************

void setup()
{
    Serial.begin(9600);
    Serial.println(F("MQ-7 Gas Sensor Flying-Fish started"));

    pinMode(analogMQ7, INPUT);
}
    
// *********************************

void loop() { 

  // A) preparation
    // turn the heater fully on
    analogWrite(analogMQ7, HIGH); // HIGH = 255
    // heat for 1 min
    delay(60000);
    // now reducing the heating power: turn the heater to approx 1,4V
    analogWrite(analogMQ7, 71.4); // 255x1400/5000
    // heat for 90 sec
    delay(90000);
    
  // B) reading    
    // CO2 via MQ7: we need to read the sensor at 5V, but must not let it heat up. So hurry!
    analogWrite(analogMQ7, HIGH); 
    delay(50); // Getting an analog read apparently takes 100uSec
    MQ7sensorValue = analogRead(analogMQ7);          
    
  // C) print the results to the serial monitor
    Serial.print("MQ-7 PPM: ");                       
    Serial.println(MQ7sensorValue);  
    
  // D) interpretation
    // Detecting range: 20ppm-2000ppm carbon monoxide
    // air quality-cases: < 200 perfect, 200 - 800 normal, > 800 - 1800 high, > 1800 abnormal
  
    if (MQ7sensorValue <= 200) 
    {
        Serial.println("Air-Quality: CO perfect");
    }
    else if ((MQ7sensorValue > 200) || (MQ7sensorValue <= 800)) // || = or
    {
        Serial.println("Air-Quality: CO normal");
    }
    else if ((MQ7sensorValue > 800) || (MQ7sensorValue <= 1800))
    {
        Serial.println("Air-Quality: CO high");
    }
    else if (MQ7sensorValue > 1800) 
    {
        Serial.println("Air-Quality: ALARM CO very high");
        delay(3000);
    }
    else
    {
        Serial.println("MQ-7 - cant read any value - check the sensor!");
    }
}