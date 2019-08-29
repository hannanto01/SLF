#include <SoftwareSerial.h>
#define BT_TX 2
#define BT_RX 3 

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void red(){
  setColor(0,255,255);  
}

void green(){
  setColor(255,255,0); 
}

void blue(){
  setColor(255,0,255);
}

SoftwareSerial mySerial(BT_TX, BT_RX);
String myString="";

void setup(){
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

}

void loop(){

  while(mySerial.available()){
    char myChar = (char)mySerial.read();
    myString += myChar;
    delay(5);
  }

  if(!myString.equals("")){
   Serial.println("Received : "+myString);
    
      if (myString == "R") red();
      if (myString == "G") green();
      if (myString == "B") blue(); 
      if (myString == "AUTO"){
        for(int i=0; i<=3; i++){
            red();  //red
            delay(5000);     
           
            blue();  //blue
            delay(5000); 
   
            green();  //green
            delay(5000); 
                 
        }
        }
        myString="";
}
}


void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
