#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>

int data2 = 0;

IoTMakers g_im;

#define deviceID    "slf201D1566368189317"            
#define authnRqtNo  "fz9v5wq66"            
#define extrSysID   "OPEN_TCP_001PTL001_1000007620"

#define WIFI_SSID   "ICT-LAB-2.4G"                       
#define WIFI_PASS   "12345678" 
#define LIGHT A3
#define TAG_ID "LIGHT"   //be carefull

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
  pinMode(LIGHT,INPUT);
  init_iotmakers();
}

void loop(){    
  static unsigned long tick = millis();
  
  if(g_im.isServerDisconnected() == 1){
    init_iotmakers();
  }

  if ( ( millis() - tick) > 500 ){
    send_ambient_light();
    tick = millis();
  }
  g_im.loop();
}


int send_ambient_light()
{
  
  int value = analogRead(LIGHT);
  int data = map(value,0,1023,1023,0);
  data2 = (21.61/(data-0.1696))*1000;
  
  Serial.print("LIGHT : ");
  Serial.print(data2);
  Serial.println(" ");
  
  if ( g_im.send_numdata(TAG_ID, (double)data) < 0 ) {
      Serial.println(F("fail"));  
      return -1;
  }
  
  return 0;   
}
