#include <Wire.h>
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define deviceID "slf201D1566368189317"
#define authnRqtNo "fz9v5wq66"
#define extrSysID "OPEN_TCP_001PTL001_1000007620"

#define WIFI_SSID "ICT-LAB-2.4G" // SSID
#define WIFI_PASS "12345678" //psswd
#define TAG_IDAX "AcX"
#define TAG_IDAY "AcY"
#define TAG_IDAZ "AcZ"
#define TAG_IDTM "Temp"
#define TAG_IDGX "GyX"
#define TAG_IDGY "GyY"
#define TAG_IDGZ "GyZ"

const int MPU = 0x68;
int16_t acx, acy, acz, tmp, gyx, gyy, gyz;

IoTMakers g_im;

void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);

  init_iotmakers();
}

void loop() {
  // put your main code here, to run repeatedly:
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  acx = Wire.read() << 8 | Wire.read();
  acy = Wire.read() << 8 | Wire.read();
  acz = Wire.read() << 8 | Wire.read();   
  tmp = Wire.read() << 8 | Wire.read();
  gyx = Wire.read() << 8 | Wire.read();
  gyy = Wire.read() << 8 | Wire.read();
  gyz = Wire.read() << 8 | Wire.read();

  int xaxis = (acx - 1090);
  int yaxis = (acy - 930);
  int zaxis = (acz - 1000);
  int temp = (tmp + 3500);

  g_im.send_numdata(TAG_IDAX, (int)xaxis);
  g_im.send_numdata(TAG_IDAY, (int)yaxis);
  g_im.send_numdata(TAG_IDAY, (int)zaxis);
  g_im.send_numdata(TAG_IDTM, (int)tmp);
  g_im.send_numdata(TAG_IDGX, (int)gyx);
  g_im.send_numdata(TAG_IDGY, (int)gyy);
  g_im.send_numdata(TAG_IDGZ, (int)gyz);

  Serial.print("xaxis : ");
  Serial.print(xaxis);
  Serial.println();
  Serial.print("yaxis : ");
  Serial.print(yaxis);
  Serial.println();
  Serial.print("zaxis : ");
  Serial.print(zaxis);
  Serial.println();
  Serial.print("temp : ");
  Serial.print(temp);
  Serial.println();
  Serial.print("G Y axis : ");
  Serial.print(gyy);
  Serial.println();
  Serial.print("G X axis : ");
  Serial.print(gyx);
  Serial.println();
  Serial.print("G Z axis : ");
  Serial.print(gyz);
  Serial.println();
  Serial.println();
  delay(1000);
  g_im.loop(); 
}
