
#include <ESP8266WiFi.h>

#define leftMotorSpeed    D1
#define rightMotorSpeed   D2
#define leftMotorDir      D3
#define rightMotorDir     D4

void setup() {
  Serial.begin(9600);
  
  pinMode(leftMotorSpeed ,OUTPUT);
  pinMode(rightMotorSpeed ,OUTPUT);
  pinMode(leftMotorDir ,OUTPUT);
  pinMode(rightMotorDir ,OUTPUT);
 
}

void loop() {
    digitalWrite(leftMotorDir,HIGH);
    digitalWrite(rightMotorDir,HIGH); 
    analogWrite(leftMotorSpeed,1020);
    analogWrite(rightMotorSpeed,1020);
    
}
