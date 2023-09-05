// import libraries
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

// define u8g2 display
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 

// constants (can change when running code)
volatile byte state = 0;
unsigned long previousMillis = 0UL;
unsigned long interval = 10000UL;

void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);                  // define data pin for button
  u8g2.begin();                              // initialise u8g2
  Serial.begin(9600);                        // initialise serial monitor
  Serial.println("Reset");                   // print "reset" in serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == 0){
    u8g2.clearBuffer();                      // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);   // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(20,29,"Brush?");            // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW){
      delay(200);
      state = 1;
      Serial.println("state1");
    }
  }

  if (state == 1){
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"brushing");           // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW)
    {
      delay(200);
      state = 0;
      Serial.println("state0");
    }
    unsigned long currentMillis = millis();

    if(currentMillis - previousMillis > interval)
    {
    state = 0;
    Serial.println("state0timed");
    // update the previousMillis value
    previousMillis = currentMillis;
    }

  }
}
