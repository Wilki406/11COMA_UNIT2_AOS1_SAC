// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
#include <Adafruit_BMP280.h>

// Libraries for SD card
#include "FS.h"
#include "SD.h"
#include <SPI.h>

#define timeFactor 1000000
#define timeToSleep 10

// Define CS pin for the SD card module
#define SD_CS 5

Adafruit_BMP280 bme;
 
// Variables for test data

float temp_value;
// Save reading number on RTC memory
RTC_DATA_ATTR int readingID = 0;
String dataMessage;

// MAC Address of responder - edit as required
uint8_t broadcastAddress[] = {0xEC, 0x62, 0x60, 0x9D, 0x73, 0xFC};
//EC:62:60:93:23:F4

// Define a data structure
typedef struct struct_message {
  char a[32];
  float c;

} struct_message;
 
// Create a structured object
struct_message myData;
 
// Peer info
esp_now_peer_info_t peerInfo;
 
// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void setup() {
 
  // Set up Serial Monitor
  Serial.begin(115200);
 
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
 
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
 
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
 
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

//  ///////// SD Card stuff //////////
//  // Initialize SD card
//  SD.begin(SD_CS);  
//  if(!SD.begin(SD_CS)) {
//    Serial.println("Card Mount Failed");
//    return;
//  }
//  uint8_t cardType = SD.cardType();
//  if(cardType == CARD_NONE) {
//    Serial.println("No SD card attached");
//    return;
//  }
//  Serial.println("Initializing SD card...");
//  if (!SD.begin(SD_CS)) {
//    Serial.println("ERROR - SD card initialization failed!");
//    return;    // init failed
//  }
//
//  // If the data.txt file doesn't exist
//  // Create a file on the SD card and write the data labels
//  File file = SD.open("/data.txt");
//  if(!file) {
//    Serial.println("File doens't exist");
//    Serial.println("Creating file...");
//    writeFile(SD, "/data.txt", "Reading ID, boardID, Temperature \r\n");
//  }
//  else {
//    Serial.println("File already exists");  
//  }
//  file.close();
//  ///////// end SD Card stuff //////////

  esp_sleep_enable_timer_wakeup(timeToSleep * timeFactor);
  
  temp_value = bme.readTemperature();
  strcpy(myData.a, "ESP16");
  myData.c = temp_value;
    // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
    Serial.println(temp_value);
//    delay(1000);
  }
  else {
    // try to send it 5 additional times.
    for (int i = 0; i < 5; i++){
      esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
      if (result == ESP_OK) {
        Serial.print("Sending confirmed. Attempts:");
        Serial.println(i+2);
        Serial.println(temp_value);
        break;
      }
      delay(100);
    }
    Serial.println("Sending error");
  }

//  logSDCard();
//
//  // Increment readingID on every new reading
//  readingID++;

  esp_deep_sleep_start();
  
}
 
void loop() {
  
}

// Write the sensor readings on the SD card
void logSDCard() {
  dataMessage = String(readingID) + "," + "ESP16" + "," +
                String(temp_value) + "\r\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.txt", dataMessage.c_str());
}

// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
