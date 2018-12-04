#include "LightSensor.h"

LightSensor::LightSensor(const uint8_t dPin, const uint8_t aPin)
  :dPin(dPin), aPin(aPin)
{
  digitalWrite(dPin,LOW);
}

uint32_t LightSensor::read() {
  Serial.println("Reading LIGHT YOH");
  digitalWrite(dPin,HIGH);
  delay(1000);
  uint32_t read = analogRead(aPin);
  digitalWrite(dPin,LOW);
  return read;
}
