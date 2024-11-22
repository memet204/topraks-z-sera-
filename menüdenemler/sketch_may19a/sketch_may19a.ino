#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);
#include <EEPROM.h>

 #define onay_butonu 6
 #define artirma_butonu 7
 #define azaltma_butonu 5


void setup()
{ 

  pinMode(onay_butonu,INPUT_PULLUP);
  pinMode(artirma_butonu,INPUT_PULLUP);
  pinMode(azaltma_butonu,INPUT_PULLUP);

}

 float ec_degeri,ph_degeri,deger;
  int menu=1;

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
  
  }

   if (menu==2){  //ph ayarı
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

 if(menu==3){  //ec ayarı
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



   
  }
