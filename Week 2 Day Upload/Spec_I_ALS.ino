#define LIGHT A3
#define LED 9
#define BUZZER 6 

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(BUZZER,OUTPUT);
}

void loop() {
  int value = analogRead(LIGHT);
  int data = map(value,0,1023,1023,0);

  Serial.print("LIGHT : ");
  Serial.println(data);

  analogWrite(LED,value);

  delay(1000);
  
  if (data <= 600){
    tone(BUZZER, 600);
    delay(100);
    noTone(BUZZER);
    delay(100);
    Serial.println("BUZZER ON");
  }
}

// map(value,fromLow,fromHigh,toLow,toHigh) = change the dynamic range of value
