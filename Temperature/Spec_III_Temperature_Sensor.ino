#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

IoTMakers g_im;

#define deviceID    "slf201D1566368189317"            
#define authnRqtNo  "fz9v5wq66"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007620"

#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 

#define ONE_WIRE_BUS 2 
#define TAG_ID "Temperature"

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);



void init_iotmakers()
{
  while(1){
     Serial.print(F("Connect to AP..."));
     
     while(g_im.begin(WIFI_SSID, WIFI_PASS)<0){ 
      Serial.println(F("retrying..."));
      delay(1000);
     }
    
    Serial.println(F("success"));
    g_im.init(deviceID, authnRqtNo, extrSysID); 
    Serial.print("Connect to platform... ");

    while ( g_im.connect() < 0 ){
      Serial.println(F("retrying."));
      delay(1000);
    }

   Serial.println(F("success"));
   Serial.print(F("Auth... "));

    if(g_im.auth_device() >= 0) {
      Serial.println(F("success "));
      return;
    }
  }
}
    

void setup(){
  Serial.begin(9600);
  sensors.begin();
  sensors.setResolution(12);
  Serial.print(F("Resolution:  "));
  Serial.println(sensors.getResolution());
  init_iotmakers();
}



void loop(){    
  static unsigned long tick = millis();
  if(g_im.isServerDisconnected() == 1){
    init_iotmakers();
  }

  if ( ( millis() - tick) > 5000 ){
    send_temperature();
    tick = millis();
  }
  g_im.loop();
}


int send_temperature()
{
  sensors.requestTemperatures(); 
  int data = sensors.getTempCByIndex(0);
 
  Serial.print("Temperature = ");
  Serial.print(data);
  Serial.print(" C");
  Serial.println(" ");
  
  if ( g_im.send_numdata(TAG_ID, (double)data) < 0 ) {
      Serial.println(F("fail"));  
      return -1;
  }
  
  return 0;   
}
