#include <Wire.h>
#include "DFRobot_EC.h"
DFRobot_EC ec;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

//ekran
int upButton = 7, downButton = 4, selectButton = 5, menu = 1;

//ph sensörü
float calibration_value = 21.34 - 0.7;
int phval = 0; 
unsigned long int avgval; 
int buffer_arr[10],temp;
float ph_act;
float ph ;

//ec sensörü
float voltage,ecValue,temperature = 25;
float AD,EC;
float Ec;

//motor
const int in2 = 2;
const int in3 = 3;
const int in4 = 4;
int bkl = 0;

void setup() {
    //ekran
    lcd.backlight();
    pinMode(upButton, INPUT_PULLUP);
    pinMode(downButton, INPUT_PULLUP);
    pinMode(selectButton, INPUT_PULLUP);
    updateMenu();
  
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
 delay(1000);
 
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
 Serial.print("S?cakl?k: ");
 Serial.println(temperature);



   //sayaç
   for(int sure=0 ; sure = 6 ; sure++){
       delay(300000);//5dk bekle
   }
   
   //motor
   if (ph_act > ph){
   
    digitalWrite(in2,LOW);//çal??t?r motor 1
    delay(bkl);// bekle
    digitalWrite(in2, HIGH );//kapat
    !digitalRead(ph_act);
   }
   
    delay(1000);//1 sn bekle
    
    if(ecValue > Ec){
    digitalWrite(in3, LOW);//çal??t?r motor 2
    delay(bkl);//10sn bekle
    digitalWrite(in3,HIGH );//kapat
    !digitalRead(ecValue);
    }
   
    delay(1000 );//1 sn bekle
    
    if(ecValue <Ec){
    digitalWrite(in4,LOW );//çal??t?r motor 3
    delay(bkl);//10sn bekle
    digitalWrite(in4,HIGH );//kapat
    !digitalRead(ecValue);
    }
   
  if (!digitalRead(downButton))
  {
    menu++;
    updateMenu();
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton))
  {
    menu--;
    updateMenu();
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton))
  {
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}

void updateMenu() 
{
  switch (menu)
  {
    case 0:
      menu = 1;
      break;
    case 1:
      lcd.clear();
      lcd.print(">ph sensoru");
      lcd.setCursor(0, 1);
      lcd.print(" ec sensoru");
      break;
    case 2:
      lcd.clear();
      lcd.print(" ph sensoru");
      lcd.setCursor(0, 1);
      lcd.print(">ec sensoru");
      break;
   case 3: 
      lcd.clear();
      lcd.print(">motor hizi");
      lcd.setCursor(0, 1);
      lcd.print(" sicaklik");
      break;
    case 4:
      lcd.clear();
      lcd.print(" motor hizi");
      lcd.setCursor(0, 1);
      lcd.print(">sicaklik");
      break;
    case 5:
      menu = 4;
      break;
  }
}

void executeAction() 
{
  switch (menu) 
  {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
      case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    
  }
}

void action1() 
{
  lcd.clear();
  lcd.print(">ph ");
   lcd.setCursor(5, 0);
   lcd.print(ph);
   lcd.setCursor(11, 0);
   lcd.print(ph_act);
  delay(15000);
  //ph buton kodu
  if (!digitalRead(downButton))
  {
   ph++;
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton))
  {
   ph--;
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton))
  {
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}
void action2() 
{
   lcd.clear();
   lcd.print(">ec ");
   lcd.setCursor(5, 0);
   lcd.print(Ec);
   lcd.setCursor(11, 0);
   lcd.print(ecValue);
  delay(15000);
  //ec artt?r azalt
  if (!digitalRead(downButton))
  {
    Ec++;
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton))
  {
    Ec--;
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton))
  {
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}
void action3() 
{
  lcd.clear();
  lcd.print(">motor sure");
  lcd.setCursor(14, 0);
  lcd.print(bkl);
  delay(15000);
  
  //h?z artt?r azalt
  if (!digitalRead(downButton))
  {
    bkl +=10000;
    delay(100);
    while (!digitalRead(downButton));
  }
  if (!digitalRead(upButton))
  {
    bkl -=10000;
    delay(100);
    while(!digitalRead(upButton));
  }
  if (!digitalRead(selectButton))
  {
    executeAction();
    updateMenu();
    delay(100);
    while (!digitalRead(selectButton));
  }
}
void action4() 
{
  lcd.clear();
  lcd.print(">sicakli");
  lcd.setCursor(11,0);
  lcd.print(temperature);
  delay(15000);
  
}