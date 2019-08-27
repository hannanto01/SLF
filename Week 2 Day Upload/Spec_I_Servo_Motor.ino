#include <Servo.h>
Servo myServo;
int angle = 0;

void setup() {
  Serial.begin(9600);
  myServo.attach(3);
}

void loop() {
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 60; angle++) 
  { 
    myServo.write(angle); 
    delay(10); 
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 60; angle > 0; angle--) 
  { 
    myServo.write(angle); 
    delay(10); 
  } 
}
