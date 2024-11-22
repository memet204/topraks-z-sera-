#include "DFRobot_EC.h"

DFRobot_EC ec;

float voltage,ecValue,temperature = 35;
float AD,EC;

void setup()
{
  Serial.begin(9600);
  ec.begin();
}
void loop(){
 for(int i=0;i<20;i++)
 {  
    AD = AD + analogRead(A0);
    delay(20);
 }
 AD = AD / 20;
 voltage = (AD/1024.0)*5000;
 ecValue = ec.readEC(voltage,temperature); 
 
 ec.calibration(voltage,temperature); 
 delay(100);
 Serial.print("EC degeri: ");
 Serial.println(voltage);
  Serial.println(ecValue);

 //Serial.print("Sıcaklık: ");
 //Serial.println(temperature);
}
