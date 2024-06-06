
/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>

int vol = -1;

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    char msg[32];
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback function that will be executed when data is received
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Received message: ");
  Serial.println(myData.msg);
  Serial2.println(myData.msg);
}
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial2.begin(19200, SERIAL_8N1, 18, 19);

  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(onDataRecv);
}
 
void loop() {
  while(Serial2.available()) {
    Serial.write(Serial2.read());
  }
  while(Serial.available()) {
    Serial2.write(Serial.read());
  }
}