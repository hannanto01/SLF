#define trigPin 13                 
#define echoPin 12                
//#define BUZZER 6
#define redPin 11 
#define greenPin 10 
#define bluePin 9


//int redPin = 11; 
//int greenPin = 10; 
//int bluePin = 9;

void setup()
{
  Serial.begin (9600);       
     
  pinMode(trigPin, OUTPUT);   
  pinMode(echoPin, INPUT);   
//  pinMode(BUZZER, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT); 
  pinMode(bluePin, OUTPUT); 
  
}

void loop()
{
  long duration, distance;                   
 
  digitalWrite(trigPin, LOW);                
  delayMicroseconds(2);                
  digitalWrite(trigPin, HIGH);            
  delayMicroseconds(10);               

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);   
  distance = duration * 17 / 1000;

  if (distance >= 200 || distance <= 0)       
  {
    Serial.println("Unable to measure distance");
  }
  else                                           
  {
    Serial.print(distance);                      
    Serial.println(" cm"); 
  }      
    if(distance < 30)
    {
      //tone(BUZZER, 600);
     // delay(distance * 10);
     // noTone(BUZZER);
     // delay(distance * 10);

      setColor(255, 0, 0); // red 
      delay(500); 
    }
    else
    {
      //delay(500);
       setColor(0, 255, 0); // green 
       delay(500);
      
    }


}


void setColor(int red, int green, int blue) 
{ 
  analogWrite(redPin,red); 
  analogWrite(greenPin,green); 
  analogWrite(bluePin,green); 
}
