#include <Wire.h>
#include "DFRobot_EC.h"
DFRobot_EC ec;

//ec

float voltage,ecValue,temperature = 25;
float AD,EC;

//ph
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;

//motor
const int in2 = 2;
const int in3 = 3;
const int in4 = 4;


void setup() {
//------   motor  ------
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

//ph
 Wire.begin();
  Serial.begin(9600);
  //ec
    ec.begin();
    
}

void loop() {
//ec
char i;
 AD = 0;
 for(i=0;i<20;i++)
 {
    AD = AD + analogRead(0);
    delay(20);
 }
 AD = AD / 20;
 voltage = (AD/1024.0)*5000;
 ecValue = ec.readEC(voltage,temperature); 
 if(ecValue > 0){EC = ecValue;}
 ec.calibration(voltage,temperature); 
 delay(100);
 Serial.print("EC degeri: ");
 Serial.println(ecValue);
 Serial.print("Sıcaklık: ");
 Serial.println(temperature);


//ph

 for(int i=0;i<10;i++) 
 { 
   buffer_arr[i]=analogRead(A0);
   delay(30);
 }
 for(int i=0;i<9;i++)
 {
   for(int j=i+1;j<10;j++)
   {
     if(buffer_arr[i]>buffer_arr[j])
     {
       temp=buffer_arr[i];
       buffer_arr[i]=buffer_arr[j];
       buffer_arr[j]=temp;
     }
   }
 }
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6; 
  ph_act = -5.70 * volt + calibration_value;
 
 Serial.print("pH Val: ");
 Serial.println(ph_act);
 delay(100);


//motor
  
while ( ph_act<7) {
      digitalWrite(in2, HIGH);//çalıştır motor 1
      delay(100);//10sn bekle
      digitalWrite(in2,LOW );//kapat
      // phValue = analogRead (analogInPin);//ph yi kotrol et

    }

    while (  true  ) {
      digitalWrite(in3, HIGH);//çalıştır motor 2
      delay(100);//10sn bekle
      digitalWrite(in3,LOW );//kapat
    }

    while ( true ) {
      digitalWrite(in4,HIGH );//çalıştır motor 3
      delay(100);//10sn bekle
      digitalWrite(in4,LOW );//kapat

    }


}
