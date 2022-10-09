#include<Servo.h>
Servo smotor;
int trigpin=12;
int echopin=13;
void setup()
{
  Serial.begin(9600);
  //Smoke
  pinMode(A1,INPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(9,OUTPUT);
  
  
  
  pinMode(2,OUTPUT);
  pinMode(A0,INPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  smotor.attach(3);
  pinMode(8,INPUT);
  pinMode(7,OUTPUT);
}

void loop()
{
  
  // Smoke
  int sensorValue = analogRead(A1);
  Serial.print("Gas sensor value: ");
  Serial.println(sensorValue);
  if(sensorValue > 600){
    digitalWrite(9,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(6,HIGH);
  }
  else{
    digitalWrite(9,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(6,LOW);
  }
  
  
  //fan 
  double temp=analogRead(A0);
  temp=(((temp/1024)*5)-0.5)*100;
  digitalWrite(2,LOW);
  Serial.print("Room temperature: ");
  Serial.println(temp);
  if (temp>35)
    digitalWrite(2,HIGH);
  
  //Door opening/closing
  digitalWrite(trigpin,LOW);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  float duration=pulseIn(echopin,HIGH);
  float distance=(duration*0.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  
  //when object within 1m.
  if (distance<100){  
    for(int i=0;i<=90;i+=5){
      smotor.write(i);
      delay(100);
    }
    delay(2000);
    for(int j=90;j>=0;j-=5){
      smotor.write(j);
      delay(100);
    }
  }
  
  //Staircase(steps)
  digitalWrite(7,LOW);
  int a=digitalRead(8);
  if(a){
    Serial.println("Motion Detected");
    digitalWrite(7,HIGH);
    delay(3000); //time to climb the stairs.
  }
  delay(100);
}