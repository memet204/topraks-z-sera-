#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int upButton = 7, downButton = 4, selectButton = 5, menu = 1;
float ph = 1;

void setup() 
{
    lcd.backlight();
    pinMode(upButton, INPUT_PULLUP);
    pinMode(downButton, INPUT_PULLUP);
    pinMode(selectButton, INPUT_PULLUP);
    updateMenu();
}

void loop() 
{
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
      lcd.print(">zamanlama");
      lcd.setCursor(0, 1);
      lcd.print(" bos");
      break;
    case 4:
      lcd.clear();
      lcd.print(" zamanlama");
      lcd.setCursor(0, 1);
      lcd.print(">bos");
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
   lcd.print(ph);
  delay(15000);
}
void action2() 
{
  lcd.clear();
  lcd.print(">ec ");
  delay(15000);
}
void action3() 
{
  lcd.clear();
  lcd.print(">zamanlama ");
  delay(15000);
}
void action4() 
{
  lcd.clear();
  lcd.print(">bos ");
  delay(15000);
}
