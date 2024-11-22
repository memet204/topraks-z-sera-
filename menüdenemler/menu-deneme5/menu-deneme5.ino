#include <EEPROM.h>
#include <Wire.h>
#include "DFRobot_EC.h"
DFRobot_EC ec;
#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);


//menü
 #define onay_butonu 6
 #define artirma_butonu 7
 #define azaltma_butonu 5

float ec_degeri,ph_degeri,deger;
  int menu=1;
  
 //ph sensörü
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;


//ec sensörü

float voltage,temperature = 25;
float AD,EC;
float ecValue;

//motor
const int in2 = 2;
const int in3 = 3;
const int in4 = 4;

  
void setup()
{ 
//tuş
  pinMode(onay_butonu,INPUT_PULLUP);
  pinMode(artirma_butonu,INPUT_PULLUP);
  pinMode(azaltma_butonu,INPUT_PULLUP);

//ph sensör
  
 Wire.begin();
 Serial.begin(9600);
  
  //ec sensör
  
  Serial.begin(9600);
ec.begin();
  
  //motor
  
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop()
{ 
  if (menu==1){
   
  lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("ec ");
   lcd.setCursor(1, 1);
  lcd.print("ph ");
  lcd.setCursor(10,0);
    lcd.print(EEPROM.get(0,deger));
    lcd.setCursor(10,1);
    lcd.print(EEPROM.get(5,deger));

  
  if(digitalRead(azaltma_butonu)==HIGH){
    while(digitalRead(azaltma_butonu)==HIGH) delay(10);
    menu=2;}

    if(digitalRead(artirma_butonu)==HIGH){
      while(digitalRead(artirma_butonu)==HIGH) delay(10);
    menu=3;}
    if(digitalRead(onay_butonu)==HIGH){
      while(digitalRead(onay_butonu)==HIGH) delay(10);
      menu=4;
      
    }}
  
  }

else if (menu==2){  //ph ayarı
    lcd.clear();
   lcd.setCursor(0,0);
    lcd.print("ph:"); 
   lcd.setCursor(10,0);
    lcd.print(ph_degeri);
    
    if(digitalRead(onay_butonu)==HIGH){
      while(digitalRead(onay_butonu)==HIGH) delay(10);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ph Hafiza");
      lcd.setCursor(0,1);
      lcd.print(" ya aliniyor....");
      EEPROM.put(5,ph_degeri);
      delay(100);
      menu=1;
    }

     else if(digitalRead(artirma_butonu)==HIGH){
      while(digitalRead(artirma_butonu)==HIGH) delay(10);
     
      ph_degeri=ph_degeri+0.01;
    }
    else if(digitalRead(azaltma_butonu)==HIGH){
      while(digitalRead(azaltma_butonu)==HIGH) delay(10);
      
      ph_degeri=ph_degeri-0.01;
    } 
     //------ec sayı sınırlayıcı-------
   
    if(ph_degeri>=14 ){
      ph_degeri=0;
      
    }
    if(ph_degeri<0){
      ph_degeri=14;
      
    } 
  }

else if(menu==3){  //ec ayarı
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ec:"); 
   lcd.setCursor(10,0);
    lcd.print(ec_degeri);

    if(digitalRead(onay_butonu)==HIGH){
      while(digitalRead(onay_butonu)==HIGH) delay(10);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("ec Hafiza");
      lcd.setCursor(0,1);
      lcd.print(" ya aliniyor....");
      EEPROM.put(0,ec_degeri);
      delay(1000);
      menu=1;
    }

     else if(digitalRead(artirma_butonu)==HIGH){
      while(digitalRead(artirma_butonu)==HIGH) delay(10);
     
      ec_degeri=ec_degeri+0.01;
    }
    else if(digitalRead(azaltma_butonu)==HIGH){
      while(digitalRead(azaltma_butonu)==HIGH) delay(10);
      
      ec_degeri=ec_degeri-0.01;
    } 
     //------ec sayı sınırlayıcı-------
   
    if(ec_degeri>=20 ){
      ec_degeri=0;
      
    }
    if(ec_degeri<0){
      ec_degeri=20;
      
    }
   }
   
//ec sensör kodları



 //ph sensörü ve kodları
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
 delay(1000);
 

   
else if(menu==4){
  
  lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("motor ");
      lcd.setCursor(0,1);
      lcd.print("30dk sonra caliscak");
      
  

 //motor
   if (ph_act > ph_degeri){
   
    digitalWrite(in2,LOW);//çalıştır motor 1
    delay(60000);//1dk  bekle
    digitalWrite(in2, HIGH );//kapat
     delay(120000);//2 dk bekle
    !digitalRead(ph_act);
   }
   
    delay(2000);//1 sn bekle
    
    if(ecValue > ec_degeri){
    digitalWrite(in3, LOW);//çalıştır motor 2
    delay(60000);//1dk bekle
    digitalWrite(in3,HIGH );//kapat
    delay(120000);//2 dk bekle
    !digitalRead(ecValue);
    }
   
    delay(1000 );//1 sn bekle
    
    if(ecValue >ec_degeri){
    digitalWrite(in4,LOW );//çalıştır motor 3
    delay(60000);// 1dk bekle
    digitalWrite(in4,HIGH );//kapat
    delay(120000);//2 dk bekle
    !digitalRead(ecValue);
    }
    
    delay(1800000);
}
   
  }
