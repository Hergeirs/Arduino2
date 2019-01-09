#include "Pump.h"
 
void MoisturePump::pump(const uint8_t wantedMoisture) {
  uint8_t currentMoisture = moistureSensor.read();
  while(currentMoisture < wantedMoisture) {
     Serial.println(currentMoisture);
     Serial.print("pin: ");
     Serial.println(powerPin);
     digitalWrite(powerPin,HIGH);
    Serial.println("pumping...");
     delay(1500);
     digitalWrite(powerPin,LOW);
     Serial.println("stopped pumping...");
     delay(10000);
     currentMoisture = moistureSensor.read();
  }
  digitalWrite(powerPin,LOW);

  Serial.println(currentMoisture);
  Serial.println("finished Pumping");
}

