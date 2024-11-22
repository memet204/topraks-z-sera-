#include <DFRobot_PH.h>

#include <Wire.h>

int pH_Value = 0, temp[99]; 
float avarege;
float ph=0;
void setup() 
{
  Wire.begin();
  Serial.begin(9600);
}
void loop() {
  pH_Value = analogRead(A1);
  ph = pH_Value / 73,07141 ;
for(int i=0;i<100;i++){
  temp[i]=ph;
  avarege+=temp[i];
  }
 avarege=avarege/100;
  //Serial.println(avarege);
 // Serial.println(pH_Value);
   Serial.println(analogRead(A1));
  delay(300);
}
