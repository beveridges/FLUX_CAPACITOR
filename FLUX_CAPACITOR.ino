#include "Adafruit_NeoPixel.h"
#include "Adafruit_LEDBackpack.h"

#define FRONT_BUTTON 35
#define TOP_LEFT 32
#define TOP_RIGHT 33
#define FRONT_BUTTON_LED 26
#define TOP_LEFT_LED 27
#define TOP_RIGHT_LED 14

#define PIN        4 // Neopixel pin
#define NUMPIXELS 24 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

#define DISPLAY_CLK 21
#define DISPLAY_DIO 22


void setup() {
  // put your setup code here, to run once:
  pinMode(FRONT_BUTTON, INPUT);
  pinMode(TOP_LEFT, INPUT);
  pinMode(TOP_RIGHT, INPUT);
  pinMode(FRONT_BUTTON_LED, OUTPUT);
  pinMode(TOP_LEFT_LED, OUTPUT);
  pinMode(TOP_RIGHT_LED, OUTPUT);
  Serial.begin(9600);

  pixels.setBrightness(0);
  pixels.show();

  alpha4.begin(0x70);  // pass in the address

  alpha4.writeDigitRaw(3, 0x0);
  alpha4.writeDigitRaw(0, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(0, 0x0);
  alpha4.writeDigitRaw(1, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(1, 0x0);
  alpha4.writeDigitRaw(2, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  alpha4.writeDigitRaw(2, 0x0);
  alpha4.writeDigitRaw(3, 0xFFFF);
  alpha4.writeDisplay();
  delay(200);
  
  alpha4.clear();
  alpha4.writeDisplay();

  // display every character, 
  for (uint8_t i='!'; i<='z'; i++) {
    alpha4.writeDigitAscii(0, i);
    alpha4.writeDigitAscii(1, i+1);
    alpha4.writeDigitAscii(2, i+2);
    alpha4.writeDigitAscii(3, i+3);
    alpha4.writeDisplay();
    
    delay(300);
  }

}

void loop() {

  if (digitalRead(FRONT_BUTTON) == true)
  { 
    Serial.println("FRONT");
    digitalWrite(FRONT_BUTTON_LED,HIGH);

    for(int v=0; v<30; v++){
      pixels.clear();
      for(int i=0; i<8;i++){
        pixels.setPixelColor(i, pixels.Color(100,100,100));
        pixels.setPixelColor((i+8), pixels.Color(100,100,100));
        pixels.setPixelColor((i+16), pixels.Color(100,100,100));
        delay(10);
        pixels.setBrightness(20+v);
        pixels.show();
    }
  }

  for(int t=50; t>-1; t--){ 
    pixels.setBrightness(t);
    delay(40);
    pixels.show();
  }



  }else{
    
    digitalWrite(FRONT_BUTTON_LED, LOW);
  }
  



  if (digitalRead(TOP_LEFT) == true)
  { 
    Serial.println("LEFT");
    digitalWrite(TOP_LEFT_LED,HIGH);

    pixels.clear();
    for(int i=0; i<8;i++){
    pixels.setPixelColor(i, pixels.Color(255,110,14));
    pixels.setPixelColor((i+8), pixels.Color(255,110,14));
    pixels.setPixelColor((i+16), pixels.Color(255,110,14));
    delay(20);
    pixels.setBrightness(23);
    pixels.show();
  }

    
  }
  else{
    pixels.setBrightness(0);
    pixels.show();
    digitalWrite(TOP_LEFT_LED, LOW);
  }




  if (digitalRead(TOP_RIGHT) == true)
  { 
    Serial.println("RIGHT");
    digitalWrite(TOP_RIGHT_LED,HIGH);
  }else{
    digitalWrite(TOP_RIGHT_LED, LOW);
  }

}

