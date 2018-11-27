
/*
 * Libraries
 */
#include "ESP8266.h"
#include <SoftwareSerial.h>
 
/*
 * Definitions
 */
#define SSID        "Kristmund Hotspot"
#define PASSWORD    "skopun240"
#define HOST_NAME   "www.google.com"
#define HOST_PORT   (80)
 
/*
 * Declarations
 */
SoftwareSerial mySerial(2, 3); /* RX:D4, TX:D3 */
ESP8266 wifi(mySerial, 115200);
uint32_t len;
 
void setup() {
  //Init debug serial connection
  Serial.begin(9600);
  Serial.println("Serial connection setup [DONE]");
 
  //Init WiFi
  while (true) {
    Serial.println("WiFi setup [START]");
    if (wifi.joinAP(SSID, PASSWORD)) {
      Serial.print("Join AP success\r\n");
      if (wifi.disableMUX()) {
        Serial.println("WiFi setup [DONE]");
        break;
      } else {
        Serial.println("WiFi setup [MUX ERR]");
      }
    } else {
      Serial.println("WiFi setup [AP ERR]");
    }
    //If init failed, wait 20s and try again
    delay(20000);
  }
}
 
void loop() {   
  uint8_t buffer[512] = {0};  
  char *request = "GET /utc/now HTTP/1.1\r\nHost: www.timeapi.org\r\nAccept-Encoding: gzip,deflate\r\nUser-Agent:ESP8266\r\nContent-Type:application/json\r\n\r\n";
  if (wifi.createTCP(HOST_NAME, HOST_PORT)) {
    if (wifi.send((const uint8_t*)request, strlen(request))) {
      Serial.println("Send data [OK]");
    }
    else {
      Serial.println("Send data [ERR]");
    }
  }
  else {
    Serial.println("Create tcp [ERR]");
  }
  len = wifi.recv(buffer, sizeof(buffer), 10000);
  if (len > 0) {
    Serial.print("Received:[");
    for (uint32_t i = 0; i < len; i++) {
      Serial.print((char)buffer[i]);
    }
    Serial.print("]\r\n");
  }
 
  if (wifi.releaseTCP()) {
    Serial.println("Release tcp [OK]");
  } else {
    Serial.println("Release tcp [ERR]");
  }
  delay(20000);
}
