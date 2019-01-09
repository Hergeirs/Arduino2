
/*
   Libraries
*/
#include "ESP8266.h"
#include "CapacitiveMoistureSensor.h"
#include "LightSensor.h"
#include "TemperatureSensor.h"
#include <SoftwareSerial.h>
#include "Pump.h"


/*
   Definitions
*/
#define SSID        "Husid Von"
#define PASSWORD    "GudJesusHeilagiAndin"
#define HOST_NAME   "192.168.1.81"
#define HOST_PORT   (8080)

/*
   Declarations
*/
SoftwareSerial mySerial(2, 3); /* RX:D4, TX:D3 */
ESP8266 wifi(mySerial, 115200);
uint32_t len;

void setup() {
    Serial.begin(9600);

  //Init debug serial connection
  Serial.begin(9600);
  Serial.println("Serial connection setup [DONE]");
  Serial.println("Allowing ESP8266 time to start...");
  delay(10000);
 

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

  Serial.println(wifi.getVersion());  
  Serial.println(wifi.getAPList());
  
}



struct Data {
  public:
    uint16_t plantId;
    uint8_t temperature;
    uint8_t moisture;
    uint32_t light;
    uint8_t water;
};


struct Package {
  union {
    Data values;
    uint8_t bytes[sizeof(Data)];
  } data;
};


class DataHandler {
  private:
    const uint16_t plantId = 1;
    Package package;
    const CapacitiveMoistureSensor& moisture;
    const TemperatureSensor temperature = TemperatureSensor(7, A1);
    const LightSensor light = LightSensor(13, A0);

    void populatePackage() {
      Data& values = package.data.values;
      values.plantId = plantId;
      values.temperature = temperature.read();
      values.moisture = moisture.read();
      values.light = light.read();
      values.water = 90;
    }

  public:
    DataHandler(const CapacitiveMoistureSensor& moistureSensor):moisture(moistureSensor) 
    {
    }
  public:
    const Package getPackage() {
      populatePackage();
      return package;
    }
};

const CapacitiveMoistureSensor moistureSensor = CapacitiveMoistureSensor(11, A5);

const DataHandler dataHandler(moistureSensor);

const MoisturePump moisturePump(8,moistureSensor);


void loop() {

  // pump water if moisture percent goes below 30
  moisturePump.pump(30);

  while(!wifi.createTCP(HOST_NAME,HOST_PORT)) {
    Serial.print("reCreating TCP connection to server: ");
    Serial.print(HOST_NAME);
    Serial.print(" on port ");
    Serial.println(HOST_PORT);
  }
  
  Package package = dataHandler.getPackage();
    
  while (!wifi.send(package.data.bytes, sizeof(package.data.bytes))) {
    Serial.println("Send data [ERR]");
  }
  Serial.println("Send data [YESMAN]");

  while(!wifi.releaseTCP()) {
    Serial.println("TCP connection to server won't release.... trying again....");
  }
  
  delay((unsigned long)1000);
}

/*
 * len = wifi.recv(buffer, sizeof(buffer), 10000);
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
 * 
 */


