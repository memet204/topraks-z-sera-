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
int pH_Value = 0, temp[50]; 
float volt,avarege;
float ph=0;


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
   digitalWrite(in2, HIGH );
    digitalWrite(in3, HIGH );
     digitalWrite(in4, HIGH );
  if (menu==1){
   
  lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("ec ");
   lcd.setCursor(1, 1);
  lcd.print("ph ");
  lcd.setCursor(4,0);
    lcd.print(EEPROM.get(0,deger));
    lcd.setCursor(4,1);
    lcd.print(EEPROM.get(5,deger));
    lcd.setCursor(11, 0);
  lcd.print(ecValue);
   lcd.setCursor(11, 1);
  lcd.print(avarege);

  
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
     //------ph sayı sınırlayıcı-------
   
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
   
   
else if(menu==4){
  
  lcd.clear();
      lcd.setCursor(0,0);
      lcd.print(" motor 30dk");
      lcd.setCursor(0,1);
      lcd.print("sonra caliscak");   
      delay(1000);
         if(digitalRead(onay_butonu)==HIGH){
      while(digitalRead(onay_butonu)==HIGH) delay(10);
      menu=1;
          }
   
 delay(1800000);
 //motor
   if (avarege > ph_degeri){
    
   lcd.setCursor(0,0);
   lcd.clear();
      lcd.print("ph dusuruluyor");
      
    digitalWrite(in2,LOW);//çalıştır motor 1
    delay(60000);//1dk  bekle
    digitalWrite(in2, HIGH );//kapat
     delay(120000);//2 dk bekle
    !digitalRead(avarege);
    
    }
   
    delay(2000);//1 sn bekle
    
    if(ecValue < ec_degeri){
      
      lcd.setCursor(0,0);
      lcd.print("ec yukseltiliyor");
      
    digitalWrite(in3, LOW);//çalıştır motor 2
    delay(60000);//1dk bekle
    digitalWrite(in3,HIGH );//kapat
    delay(120000);//2 dk bekle
    !digitalRead(ecValue);
    }
   
    delay(1000 );//1 sn bekle
    
    if(ecValue < ec_degeri){
  
    digitalWrite(in4,LOW );//çalıştır motor 3
    delay(60000);// 1dk bekle
    digitalWrite(in4,HIGH );//kapat
    delay(120000);//2 dk bekle
    !digitalRead(ecValue);
    }   
   }

  //ec sensör kodları
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
 delay(1000);
 Serial.print("EC degeri: ");
 Serial.println(ecValue);
 Serial.print("Sıcaklık: ");
 Serial.println(temperature);


  //ph sensörü ve kodları
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
