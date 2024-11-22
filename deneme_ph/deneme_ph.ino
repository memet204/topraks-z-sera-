#include <AnalogPHMeter.h>
#include <Wire.h> 

#define SensorPin A0             // pH metrenin Arduino'ya Analog 1 pininden bağlanmasını sağlar.
#define orneklemeAraligi 20       // Ortalama işlemi için kaç adet örnekleme alınacağı.
#define printAraligi 2000         // Kaç saniyede bir ölçülen değerin ekrana yansıtılacağı.
#define arrayUzunlugu  40         // Kaç kere ölçüm alınacağını belirtir.

int pHArray[arrayUzunlugu];       // Sensörden alınan verileri saklayan array.
int pHArrayIndex=0;               // Arrayin başladığı index.


void setup()
{
   Wire.begin();
  Serial.begin(9600);   // 9600 baud rate'de seri haberleşmeyi başlatır.
}


void loop()
{
  unsigned long orneklemeZaman = millis();  // Zaman tanımları.
  unsigned long printZaman = millis();
  float pH_degeri;                          // Ölçüm değeri için pH ve gerilim değişkenleri.
  float gerilim;
  
  if(millis()-orneklemeZaman > orneklemeAraligi) // pH değeri ölçümünü yapan kod.
  {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==arrayUzunlugu)pHArrayIndex=0;
      gerilim = ortalamaArray(pHArray, arrayUzunlugu)*5.0/1024;
      pH_degeri = 3.5*gerilim;
      orneklemeZaman=millis();
  }
  
  if(millis() - printZaman > printAraligi)   //Her 2 saniyede ölçülen pH değerini ekrana yansıtır.
  {
        Serial.print("pH ölçümü: ");
        Serial.println(pH_degeri);
  }
}


double ortalamaArray(int* arr, int sayi){     // Ekrana yansıtılacak bir ölçüm için 20 adet örnek alıp
  int i;                                      // bu örneklerin ortalamasını hesaplayarak
  int max,min;                                // ve stabil sonuçlar elde edilmesini sağlar.
  double ort;
  long miktar = 0;
  if(sayi<=0){        // Ölçüm sayısı 0 ise ekrana herhangi bir değer yansıtılmaz.
    return 0;
  }
  
  if(sayi<5){         // Ölçüm sayısı 5'ten az ise ortalamayı basit işlemler ile geri döndürür.
    for(i=0;i<sayi;i++){
      miktar+=arr[i];
    }
    ort = miktar/sayi;
    return ort;
  }
  else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<sayi;i++){
      if(arr[i]<min){
        miktar+=min;       
        min=arr[i];
      }else {
        if(arr[i]>max){
          miktar+=max;    
          max=arr[i];
        }else{
          miktar+=arr[i]; 
        }
      }
    }
    ort = (double)miktar/(sayi-2);
  }
  return ort;
}
