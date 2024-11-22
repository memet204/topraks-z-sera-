#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);
 #include <EEPROM.h>

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
  int menu=0,kayan_yazi=0,saniye=0,dakika=0,saat=0,gun=0;
  int sayfa=1 ;
  float deger;
  float ph_degeri;
  float ec_degeri;
  
void setup()
{ 
  lcd.clear();
   lcd.print("1. asama tmm");
   delay(3000);

Serial.begin(9600);

  pinMode(onay_butonu,INPUT_PULLUP);
  pinMode(artirma_butonu,INPUT_PULLUP);
  pinMode(azaltma_butonu,INPUT_PULLUP);

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
 

    if(dakika>59){
      dakika=0;
     saat++;
      }
    if(saat>23){
      saat=0;
      gun++;
    }
  if(gun>21){
      gun=0;
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
     lcd.clear();
    lcd.setCursor(1, 0);
  lcd.print("*EC:");
   lcd.setCursor(1, 1);
  lcd.print("*PH:");
  
  
  
   lcd.setCursor(5, 1);
  lcd.print(ph_degeri);

  lcd.setCursor(5, 0); 
 lcd.print(EEPROM.get(0,deger));

 lcd.setCursor(12, 0); 
 lcd.print(EEPROM.get(0,deger));
 
 lcd.setCursor(12, 1);
  lcd.print(EEPROM.get(5,ph_degeri));

 delay(100);
 sayfa=0;
  
  //---------------------menü ayar kısmı ----------------------
  
if(digitalRead(onay_butonu)==0 && sayfa==0  ){
  while(digitalRead(onay_butonu)==0) delay(10);

 delay(100);
  sayfa =1;
     while( sayfa==1){
    


  if(menu==0){//******************0000000000000000000
    
    lcd.setCursor(0,0);
lcd.print("sera  otomasyonu ");
   
    for(kayan_yazi=17; kayan_yazi>=0; kayan_yazi--){
      lcd.setCursor(kayan_yazi,1);
      lcd.print(" Baslatiliyor....    ");
      
      for(int dongu=0; dongu<=30; dongu++){
        delay(3);
       menu=5;
            }
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
 lcd.print(EEPROM.get(0,deger));
 
 lcd.setCursor(12, 1);
  lcd.print(EEPROM.get(5,ph_degeri));

  if(digitalRead(onay_butonu)==0 && sayfa==1  ){
    while(digitalRead(onay_butonu)==0) delay(10);
    sayfa=0;
   }
  
delay(1000);
  
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
    lcd.print("    PH Ayari   ");
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
  delay(100);
   
    if(digitalRead(onay_butonu)==0){
      while(digitalRead(onay_butonu)==0) delay(10);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("EC Hafiza");
      lcd.setCursor(0,1);
      lcd.print("  aliniyor....");
      EEPROM.put(0,ec_degeri);
      delay(500);
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
    lcd.print(EEPROM.get(0,deger)); 
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
      Serial.print(EEPROM.get(5,ph_degeri));
      delay(1000);
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
 lcd.print(EEPROM.get(0,deger));
 
 lcd.setCursor(12, 1);
  lcd.print(EEPROM.get(5,ph_degeri));

  if(digitalRead(onay_butonu)==0 && sayfa==1  ){
    while(digitalRead(onay_butonu)==0) delay(10);
    sayfa=0;
   }
  
delay(1000);
  
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
  }}}}
