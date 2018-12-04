#ifndef LIGHTSENSORH
#define LIGHTSENSORH

#include <Arduino.h>
#include <SoftwareSerial.h>


class LightSensor {
  private:
    const uint8_t aPin;
    const uint8_t dPin;
  public:
    LightSensor(const uint8_t dPin, const uint8_t aPin);
    uint32_t read();
  
};

#endif
