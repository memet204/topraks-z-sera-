const int in2 = 2;
const int in3 = 3;
const int in4 = 4;

void setup() 
{
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
 
void loop() 
{
    digitalWrite(in2,LOW);//çalıştır motor 1
    delay(1000);//10sn bekle
    digitalWrite(in2, HIGH );//kapat
    
    delay(1000);//1 sn bekle
    
    digitalWrite(in3, LOW);//çalıştır motor 2
    delay(10000);//10sn bekle
    digitalWrite(in3,HIGH );//kapat
    
    delay(1000);//1 sn bekle
    
    digitalWrite(in4,LOW );//çalıştır motor 3
    delay(10000);//10sn bekle
    digitalWrite(in4,HIGH );//kapat
   
}
