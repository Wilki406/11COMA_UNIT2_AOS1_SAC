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
unsigned long interval = 120000UL; // this is how long it will brush for in milliseconds


// Speaker pin
int speakerPin = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(4, INPUT_PULLUP);                  // define data pin for button
  pinMode(6, INPUT_PULLUP);                  // define data pin for button
  u8g2.begin();                              // initialise u8g2
  Serial.begin(9600);                        // initialise serial monitor
  Serial.println("Reset");                   // print "reset" in serial monitor
}

void loop() {
  // put your main code here, to run repeatedly:
  if (state == 0){ //main state for nothing happening
    u8g2.clearBuffer();                      // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);   // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(20,29,"Brush?");            // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW){
      delay(200);
      state = 5;
      Serial.println("state1");
    }

    if (digitalRead(6) == LOW){
      delay(200);
      state = 2;
      Serial.println("state2");
    }
  }

  if (state == 1){ //state for brushing sequence
    u8g2.clearBuffer();                      // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"brushing");           // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW)
    {
      delay(200);
      state = 0;
      Serial.println("state0");
    }
    unsigned long currentMillis = millis(); // millis function used to time a specfic state so after a desired time the state can change

    if(currentMillis - previousMillis > interval)
    {
      delay(500);
      state = 6;
      Serial.println("state4timed");
      // update the previousMillis value
      previousMillis = currentMillis;
    }

  }

  if (state == 2){ // state to display "battery life"
    u8g2.clearBuffer();                      
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"100%");           // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW)
    {
      delay(200);
      state = 1;
      Serial.println("state1");
    }
    
    if(digitalRead(6) == LOW)
    {
      delay(200);
      state = 3;
      Serial.println("state3");

    }
  }

  if (state == 3){ // state to display brush time duration
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"2 MIN");           // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    if (digitalRead(4) == LOW)
    {
      delay(200);
      state = 1;
      Serial.println("state1");
    }
    
    if(digitalRead(6) == LOW)
    {
      delay(200);
      state = 2;
      Serial.println("state2");
    }
  }

  if (state == 4){ // state to say thanks after completing desired brush sequence time
    u8g2.clearBuffer(); 
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"Thanks");           // write something to the internal memory
    u8g2.sendBuffer();                       // transfer internal memory to the display

    delay(1500);
    state = 0;
  }

  if (state == 5){ // brushing state to play speaker tone.
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"brushing");           // write something to the internal memory
    u8g2.sendBuffer();

    tone(speakerPin, 1000, 150);

    delay(150);
    state = 1;
  
  }

  if (state == 6){ // state made for playing speaker tone and displaying thank you.
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso28_tr);
    u8g2.drawStr(0,29,"Thanks");           // write something to the internal memory
    u8g2.sendBuffer();

    tone(speakerPin, 1000, 150);

    delay(150);
    state = 4;
  
  }
}
