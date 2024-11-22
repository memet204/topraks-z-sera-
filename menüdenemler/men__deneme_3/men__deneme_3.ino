#include <EEPROM.h>
#include <Wire.h>
#include "DFRobot_EC.h"
DFRobot_EC ec;
#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);

//-------menu-------
 #define onay_butonu 6
 #define artirma_butonu 7
 #define azaltma_butonu 5
 
 byte yok[8]=
{
   B00100,
   B01110,
   B11111,
   B01110,
   B01110,
   B01110,
   B01110,
   B01110,
};
byte aok[8]=
{
   B01110,
   B01110,
   B01110,
   B01110,
   B01110,
   B11111,
   B01110,
   B00100,
};

  float isi=22,nem=10,c=1;
  int menu=0,kayan_yazi=0,saniye=0;
  int sayfa=1 ;
  float deger;
  float ph_degeri;
  float ec_degeri;
  int sayac = 0;
  int btb =0;
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
  //-------------menü--------
  lcd.clear();
   lcd.print("1. asama tmm");
   delay(3000);

Serial.begin(9600);

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
  
  

  //***********************************************************
   
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;
 
    OCR1A = 15624;

    TCCR1B |= (1 << WGM12);
 
    TCCR1B |= (1 << CS12) | (1 << CS10);  
 
    TIMSK1 |= (1 << OCIE1A);
   
    sei();
}

//******************************************************

 
ISR(TIMER1_COMPA_vect){
 
  saniye=saniye+1;
    if(saniye>59){
     saniye=0;
      
      c--;
    }
 
  if(menu==5){
 
   if(digitalRead(azaltma_butonu)==0){
       delay(150);
    menu=1;
   }
   if(digitalRead(onay_butonu)==0){
  delay(150);
     
   }
}} 
//*******************************************************

void loop()
{ 
  sayfa=0;
     lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("*EC:");
   lcd.setCursor(1, 1);
  lcd.print("*PH:");
  
  
  
   lcd.setCursor(5, 1);
  lcd.print(EEPROM.get(5,ph_degeri));

  lcd.setCursor(5, 0); 
 lcd.print(EEPROM.get(0,deger));

 lcd.setCursor(12, 0); 
 lcd.print(ecValue);
 
 lcd.setCursor(12, 1);
  lcd.print(ph_act);

 delay(100);
 

 //ph sensörü

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
 
//ec semsörü

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
  
  //---------------------menü ayar kısmı ----------------------
  
if( sayfa==0 ){
 
   
    delay(100);
sayfa=1;


    while(sayfa == 1){
      
    
    
  if(menu==0){//******************0000000000000000000
    
    lcd.setCursor(0,0);
lcd.print("ayarlar acılıyor ");
   
    for(kayan_yazi=17; kayan_yazi>=0; kayan_yazi--){
      lcd.setCursor(kayan_yazi,1);
      lcd.print(" Baslatiliyor....    ");
      
      for(int dongu=0; dongu<=30; dongu++){
        delay(5);
       menu=5;}
    }
    }
    else if(menu==1){//**************11111111111111
      lcd.clear();
  lcd.setCursor(1,0);
    lcd.print("EC Ayari");
    lcd.createChar(1,yok); 
  lcd.setCursor(8,1);
 
  lcd.write(1);
    
    delay(100);
    
    if(digitalRead(onay_butonu)==0){
      while(digitalRead(onay_butonu)==0) delay(10);
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("EC ayari");
      lcd.setCursor(0,1);
      lcd.print(" yapiniz....");
      delay(100);
      menu=2;
  }

 if(digitalRead(artirma_butonu)==0){
    while(digitalRead(artirma_butonu)==0) delay(10);
  menu=11;
  }}
  
  else if(menu==11){          //**************11 11 11 11 11  ********
       lcd.setCursor(0,0);
    lcd.print("     PH Ayari   ");
      lcd.createChar(1,aok); 
  lcd.setCursor(8,1);   
  lcd.write(1);
    delay(100);
      if(digitalRead(onay_butonu)==0){
     
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("PH ayari");
      lcd.setCursor(0,1);
      lcd.print(" yapiniz....");
      delay(100);
      menu=8;}
        if(digitalRead(azaltma_butonu)==0){
    lcd.clear();
    menu=1;}
     }
  
  else if(menu==2){           //******************22222222222222222
    lcd.setCursor(10,0);
    lcd.print(ec_degeri); 
    lcd.createChar(1,yok); 
  lcd.setCursor(0,0);   
  lcd.write(1);
  lcd.createChar(2,aok); 
  lcd.setCursor(0,1);   
  lcd.write(2);
  delay(10);
   
    if(digitalRead(onay_butonu)==0){
      while(digitalRead(onay_butonu)==0) delay(10);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("EC Hafiza");
      lcd.setCursor(0,1);
      lcd.print("  aliniyor....");
      EEPROM.put(0,ec_degeri);
      Serial.print(EEPROM.get(0,deger));
      delay(100);
      menu=3;
      
    }
    else if(digitalRead(artirma_butonu)==0){
      while(digitalRead(artirma_butonu)==0) delay(10);
     
      ec_degeri=ec_degeri+0.10;
    }
    else if(digitalRead(azaltma_butonu)==0){
      while(digitalRead(azaltma_butonu)==0) delay(10);
      
      ec_degeri=ec_degeri-0.10;
    }

   //------ec sayı sınırlayıcı-------
   
    if(ec_degeri>=14 ){
      
      ec_degeri=0;
      
    }
    if(ec_degeri<0){
      ec_degeri=14;
      
    }
    lcd.setCursor(10,0);
    lcd.print(ec_degeri); 
    lcd.setCursor(1,1);
    lcd.print("           ");
  }
  else if(menu==3){//*************************33333333333333
    
    lcd.setCursor(0,0);
    lcd.print(EEPROM.get(0,deger)); //--
    lcd.setCursor(4,0);
    lcd.print("\337C");
    lcd.setCursor(5,0);
    lcd.print(" ayarlansin?");
    lcd.setCursor(0,1);
    lcd.print("Onay tus basiniz");
    
     if(digitalRead(azaltma_butonu)==0){
    menu=1;}
    if(digitalRead(onay_butonu)==0){
      menu=5;
     
       lcd.clear();
    }
  }


 else if(menu==8){//******************8888888888888888
    lcd.setCursor(10,0);
    lcd.print(ph_degeri);
  lcd.createChar(1,yok); 
  lcd.setCursor(0,0);   
  lcd.write(1);
  lcd.createChar(2,aok); 
  lcd.setCursor(0,1);   
  lcd.write(2);
  delay(100);
  
   
    if(digitalRead(onay_butonu)==0){
      while(digitalRead(onay_butonu)==0) delay(10);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PH  Hafiza ");
      lcd.setCursor(0,1);
      lcd.print(" ya aliniyor....");
      EEPROM.put(5,ph_degeri);
      delay(100);
      menu=9;
      
    }
    else if(digitalRead(artirma_butonu)==0){
      while(digitalRead(artirma_butonu)==0) delay(10);
     
      ph_degeri=ph_degeri+1.0;
      
    }
    else if(digitalRead(azaltma_butonu)==0){
      while(digitalRead(azaltma_butonu)==0) delay(10);
      
      ph_degeri=ph_degeri-1.0;
    }
    //------- ph sayı sınırlayıcı----------
    
    if(ph_degeri>=14 ){
      
      ph_degeri=0;
      
    }
    if(ph_degeri<0){
      ph_degeri=14;
      
    }
   
    lcd.setCursor(10,0);
    lcd.print(ph_degeri);
    lcd.setCursor(1,1);
    lcd.print("             ");
  }
  else if(menu==9){//*************************9999999999
    
    lcd.setCursor(0,0);
    lcd.print(EEPROM.get(5,ph_degeri));
    lcd.setCursor(4,0);
    lcd.print("%");
    lcd.setCursor(5,0);
    lcd.print(" ayarlansin?");
    lcd.setCursor(0,1);
    lcd.print("Onay START Buton");
 
     if(digitalRead(azaltma_butonu)==0){
    menu=1;}
    if(digitalRead(onay_butonu)==0){
      menu=5;
     
       lcd.clear();
    }
     }
  
 else if(menu==5){//***************55555555555555555555555555555
 
  lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("EC:");
   lcd.setCursor(1, 1);
  lcd.print("PH:");
 
   lcd.setCursor(5, 1);
  lcd.print(EEPROM.get(5,ph_degeri));

  lcd.setCursor(5, 0); 
 lcd.print(EEPROM.get(0,deger));

 lcd.setCursor(12, 0); 
 lcd.print(ecValue);
 
 lcd.setCursor(12, 1);
  lcd.print(ph_act);

  if(digitalRead(onay_butonu)==0 && sayfa==1  ){
    sayfa=0;
   }
  
delay(200);
  
}
 else if(menu==7)
 {
     
    menu=5;
   lcd.clear();
 }
  else if(menu==6){//********************6666666666666666666666
       
    delay(1000);
  
     c=240;
    menu=5;
 lcd.clear();
  }

  //ph sensörü

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
 delay(300);
 
//ec semsörü

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
  }}


 while(sayac == 0){
  
sayac=1;
 
   //motor
   if (ph_act > ph_degeri){
   
    digitalWrite(in2,LOW);//çalıştır motor 1
    delay(600);//1dk  bekle
    digitalWrite(in2, HIGH );//kapat
     delay(1200);//2 dk bekle
    !digitalRead(ph_act);
   }
   
    delay(2000);//1 sn bekle
    
    if(ecValue > ec_degeri){
    digitalWrite(in3, LOW);//çalıştır motor 2
    delay(600);//1dk bekle
    digitalWrite(in3,HIGH );//kapat
    delay(1200);//2 dk bekle
    !digitalRead(ecValue);
    }
   
    delay(1000 );//1 sn bekle
    
    if(ecValue >ec_degeri){
    digitalWrite(in4,LOW );//çalıştır motor 3
    delay(600);// 1dk bekle
    digitalWrite(in4,HIGH );//kapat
    delay(1200);//2 dk bekle
    !digitalRead(ecValue);
    }
    while(sayac ==1){
        delay(1800000);
        sayac=0;
      
    }
   }
  }
 
