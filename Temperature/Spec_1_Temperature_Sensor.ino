#include <OneWire.h>

OneWire ds(2);

void setup(){
 Serial.begin(9600);
}

void loop(){
  static unsigned long tick = millis();
  
  if ( ( millis() - tick) > 1000 ){
    baca_data();
    tick = millis();
  }

}


 void baca_data(){
   byte i;
  byte present = 0;

  byte data[12];
  byte addr[8];
  float Temp;

  if(!ds.search(addr)){
    ds.reset_search();
    return;
  }

ds.reset();
ds.select(addr);
ds.write(0x44,1);   //start conversion, with parasite power on at the end
delay(10);

present = ds.reset();
ds.select(addr);
ds.write(0xBE);     //Read all data of Scraptchpad

for (i=0; i<9; i++)
  data[i] = ds.read();

  
  
Temp=(data[1]<<8)+data[0];    //Calculate the Celcius
Temp=Temp/16;

Serial.print("C=");   //Celcius output
Serial.println(Temp);
//Serial.print(",");
//Serial.println(" ");
 }
