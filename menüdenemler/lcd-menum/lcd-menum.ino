#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27,16,2);
 
 #define buzzer A5
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




void setup()
{ 


  pinMode(buzzer,OUTPUT);
 digitalWrite(3,1);
digitalWrite(A2,1);
digitalWrite(A3,1);
digitalWrite(A4,1);
  Serial.begin(9600);
//  lcd.begin(16,2);

digitalWrite(buzzer,1);
delay(500);
digitalWrite(buzzer,0);




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

 float isi=22,nem=10,sicaklik_degeri=10,nem_degeri=10,c=1;
  int menu=0,kayan_yazi=0,saniye=0,dakika=0,saat=0,gun=0;
 


ISR(TIMER1_COMPA_vect){
 
  saniye=saniye+1;
    if(saniye>59){
     saniye=0;
      dakika++;
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
       digitalWrite(buzzer,1); delay(1000);
      digitalWrite(buzzer,0); delay(150);
    menu=1;
   }
   if(digitalRead(onay_butonu)==0){
     digitalWrite(buzzer,1); delay(1000);
      digitalWrite(buzzer,0); delay(150);
    menu=7;
   }
}}
 
  

//*******************************************************

void loop()
{ 



  if(menu==0){//******************0000000000000000000
    
    lcd.setCursor(0,0);
lcd.print("MAKiNA          ");
   
    for(kayan_yazi=17; kayan_yazi>=0; kayan_yazi--){
      lcd.setCursor(kayan_yazi,1);
      lcd.print(" Baslatiliyor.... ");
      
      for(int dongu=0; dongu<=30; dongu++){
        delay(1);
       menu=5;}
    }
    }
    else if(menu==1){//**************11111111111111
      lcd.clear();
  lcd.setCursor(1,0);
    lcd.print("Sicaklik Ayari");
    lcd.createChar(1,yok); 
  lcd.setCursor(8,1);   
  lcd.write(1);
    
    delay(100);
    
    if(digitalRead(onay_butonu)==0){
      while(digitalRead(onay_butonu)==0) delay(10);
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Sicaklik ayari");
      lcd.setCursor(0,1);
      lcd.print(" yapiniz....");
      delay(1000);
      menu=2;
  }
 if(digitalRead(artirma_butonu)==0){
    while(digitalRead(artirma_butonu)==0) delay(10);
  menu=11;
  }}
  
  else if(menu==11){//**************11 11 11 11 11  ********
       lcd.setCursor(0,0);
    lcd.print("    Nem Ayari   ");
      lcd.createChar(1,aok); 
  lcd.setCursor(8,1);   
  lcd.write(1);
    delay(100);
      if(digitalRead(onay_butonu)==0){
     
       lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Nem ayari");
      lcd.setCursor(0,1);
      lcd.print(" yapiniz....");
      delay(100);
      menu=8;}
        if(digitalRead(azaltma_butonu)==0){
    lcd.clear();
    menu=1;}
     }
  
  else if(menu==2){//******************22222222222222222
    lcd.setCursor(10,0);
    lcd.print(sicaklik_degeri);
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
      lcd.print("Sicaklik Hafiza");
      lcd.setCursor(0,1);
      lcd.print(" ya aliniyor....");
      delay(1000);
      menu=3;
      
    }
    else if(digitalRead(artirma_butonu)==0){
      while(digitalRead(artirma_butonu)==0) delay(10);
     
      sicaklik_degeri=sicaklik_degeri+0.1;
    }
    else if(digitalRead(azaltma_butonu)==0){
      while(digitalRead(azaltma_butonu)==0) delay(10);
      
      sicaklik_degeri=sicaklik_degeri-0.1;
    }
   
    lcd.setCursor(10,0);
    lcd.print(sicaklik_degeri);
    lcd.setCursor(1,1);
    lcd.print("              ");
  }
  else if(menu==3){//*************************33333333333333
    
    lcd.setCursor(0,0);
    lcd.print(sicaklik_degeri);
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
    lcd.print(nem_degeri);
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
      lcd.print("NEM   Hafiza ");
      lcd.setCursor(0,1);
      lcd.print(" ya aliniyor....");
      delay(1000);
      menu=9;
      
    }
    else if(digitalRead(artirma_butonu)==0){
      while(digitalRead(artirma_butonu)==0) delay(10);
     
      nem_degeri=nem_degeri+0.1;
    }
    else if(digitalRead(azaltma_butonu)==0){
      while(digitalRead(azaltma_butonu)==0) delay(10);
      
      nem_degeri=nem_degeri-0.1;
    }
   
    lcd.setCursor(10,0);
    lcd.print(nem_degeri);
    lcd.setCursor(1,1);
    lcd.print("               ");
  }
  else if(menu==9){//*************************9999999999
    
    lcd.setCursor(0,0);
    lcd.print(nem_degeri);
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
  lcd.print("ISI ");
   lcd.setCursor(1, 1);
  lcd.print("Nem ");
  
  
  
   lcd.setCursor(5, 1);
  lcd.print(nem_degeri,1);

  lcd.setCursor(5, 0); 
 lcd.print(sicaklik_degeri,1);

  
  if (nem>=nem_degeri){
    lcd.setCursor(0, 1);
  lcd.print(" ");
  }
  
  if (nem<nem_degeri-1.9){
    lcd.setCursor(0, 1);
  lcd.print("*");
  }
  if (isi>=sicaklik_degeri-0.3){
    lcd.setCursor(0, 0);
  lcd.print(" ");
  }
  if (isi<sicaklik_degeri-0.9){
    lcd.setCursor(0, 0);
  lcd.print("*");
  }
   if (isi>=sicaklik_degeri+0.2){
    lcd.setCursor(9, 0);
  lcd.print("  ");
  }
  if (isi<sicaklik_degeri-0.9){
    lcd.setCursor(9, 0);
  lcd.print(" *");
  }
 
delay(1000);
  

}
 else if(menu==7)
 {
      lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(1, 0);
    lcd.print(gun);
   lcd.setCursor(3, 0);
    lcd.print("GUN");
    lcd.setCursor(10, 0);
    lcd.print(saat);
    lcd.setCursor(12, 0);
    lcd.print("SAAT");
   lcd.setCursor(0, 1);
    lcd.print(dakika);
    lcd.setCursor(3, 1);
    lcd.print("DAKIKA");
    lcd.setCursor(14, 1);
    lcd.print(saniye);
    delay(100);
    
    menu=5;
   lcd.clear();
 }
  else if(menu==6){//********************6666666666666666666666
    lcd.setCursor(0,0);
    lcd.print("cevirme         ");
    lcd.setCursor(11,0);
    lcd.print("15 sn");
    lcd.setCursor(0,1);
    lcd.print("       yapiliyor");
  
    delay(15000);
    
    delay(1000);
  
     c=240;
    menu=5;
 lcd.clear();
  }
}
