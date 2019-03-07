#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>

#define PIN D5
#define NUMPIXELS 2
#define BLYNK_PRINT Serial
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
Serial.begin(9600);
Blynk.begin("7b33b2482f1b48cdbd2e84a386937e38", "Sprite-wifi", "0837177022");
pixels.begin();
}
BLYNK_WRITE(V5)
{

int R = param[0].asInt();
int G = param[1].asInt();
int B = param[2].asInt();
Serial.println(R);
Serial.println(G);
Serial.println(B);
for(int i=0;i<NUMPIXELS;i++){

pixels.setPixelColor(i, pixels.Color(R,G,B));

pixels.show();
}
}

BLYNK_WRITE(V6){
  Serial.print("v6:") ;
  Serial.println(param.asInt());
  if(param.asInt()){
  pixels.setPixelColor(0, pixels.Color(255,153,51));
  } else {
    pixels.setPixelColor(0, pixels.Color(0,0,0));
  }
  pixels.show();
} 
void loop()
{
Blynk.run();
}
