#ifndef PUMPH
#define PUMPH
#include<Arduino.h>
#include"CapacitiveMoistureSensor.h"

class MoisturePump {
  public:
    MoisturePump(const uint8_t powerPin,const CapacitiveMoistureSensor& moistureSensor):powerPin(powerPin),moistureSensor(moistureSensor)
    {
      pinMode(powerPin,OUTPUT);
      digitalWrite(powerPin,LOW);  
    }
    void pump(const uint8_t wantedMoisture);
  private:
    const uint8_t powerPin;
    const CapacitiveMoistureSensor& moistureSensor;
  
};



#endif
