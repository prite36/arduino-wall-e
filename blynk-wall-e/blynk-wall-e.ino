#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

#define leftMotorSpeed  D1
#define rightMotorSpeed D2
#define leftMotorDir    D3
#define rightMotorDir   D4

#define servoDir D5 

char auth[] = "7b33b2482f1b48cdbd2e84a386937e38";
char ssid[] = "prite-iot";
char pass[] = "0837177022";

int minRange = 312;
int maxRange = 712;

int minSpeed = 450;
int maxSpeed = 1020;
int noSpeed = 0;


void moveControl(int x, int y)
{
  /*
    if(x == 512 && y == 512){
    analogWrite(leftMotorSpeed,noSpeed);
  } else if (y> 512){
    digitalWrite(leftMotorDir,HIGH);
    analogWrite(leftMotorSpeed,y);
  } else if (y < 512) {
    digitalWrite(leftMotorDir, LOW);
    analogWrite(leftMotorSpeed, 512+(511-y));
  }
  */

  if(y >= maxRange && x >= minRange && x <= maxRange) //zataci R
  {
    digitalWrite(rightMotorDir,HIGH); 
    digitalWrite(leftMotorDir,HIGH);
    analogWrite(rightMotorSpeed,maxSpeed);
    analogWrite(leftMotorSpeed,maxSpeed);
  }
 
  // move forward right
  else if(x >= maxRange && y >= maxRange)   //zataci R
  {
    digitalWrite(rightMotorDir,HIGH);
    digitalWrite(leftMotorDir,HIGH);
   analogWrite(rightMotorSpeed,minSpeed);
    analogWrite(leftMotorSpeed,maxSpeed);
  }

  // move forward left
  else if(x <= minRange && y >= maxRange)
  {
    digitalWrite(rightMotorDir,HIGH);
    digitalWrite(leftMotorDir,HIGH);
    analogWrite(rightMotorSpeed,maxSpeed);
    analogWrite(leftMotorSpeed,minSpeed);
  }

  // neutral zone
  else if(y < maxRange && y > minRange && x < maxRange && x > minRange)
  {
    analogWrite(rightMotorSpeed,noSpeed);
    analogWrite(leftMotorSpeed,noSpeed);
  }

 // move back
  else if(y <= minRange && x >= minRange && x <= maxRange)
  {
    digitalWrite(rightMotorDir,LOW);
    digitalWrite(leftMotorDir,LOW);
   analogWrite(rightMotorSpeed,maxSpeed);
    analogWrite(leftMotorSpeed,maxSpeed);
  }

  // move back and right
 else if(y <= minRange && x <= minRange)
  {
   digitalWrite(rightMotorDir,LOW);
    digitalWrite(leftMotorDir,LOW);
    analogWrite(rightMotorSpeed,minSpeed);
    analogWrite(leftMotorSpeed,maxSpeed); 
  }

  // move back and left
  else if(y <= minRange && x >= maxRange)
  {
    digitalWrite(rightMotorDir,LOW);
    digitalWrite(leftMotorDir,LOW);
    analogWrite(rightMotorSpeed,maxSpeed);
    analogWrite(leftMotorSpeed,minSpeed);
  }

  
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  // initial settings for motors off and direction forward
  pinMode(rightMotorSpeed, OUTPUT);
  pinMode(leftMotorSpeed, OUTPUT);
  pinMode(rightMotorDir, OUTPUT);
  pinMode(leftMotorDir, OUTPUT);
 
  digitalWrite(rightMotorSpeed, LOW);
  digitalWrite(leftMotorSpeed, LOW);
  digitalWrite(rightMotorDir, HIGH);
  digitalWrite(leftMotorDir,HIGH);
  
  servo.attach(servoDir);
  servoGo(90);
 }


void loop()
{
 
  Blynk.run();
}


BLYNK_WRITE(V1)
{
  int x = param[0].asInt();
  int y = param[1].asInt();

  moveControl(x,y);
}
BLYNK_WRITE(V2)
{
   servo.write(param.asInt());
}
void servoGo(byte finalAngle){
   byte currentAngle = servo.read();   //servo position
   if (finalAngle > currentAngle) {
    for (int i = currentAngle; i < finalAngle ; i++){
     servo.write(i); 
     delay(50);   } }
   else {
   for (int i = currentAngle; i > finalAngle ; i--){
     servo.write(i); 
     delay(50);   } }
}
