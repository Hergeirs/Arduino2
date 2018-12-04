#ifndef CAPACITIVEMOISTURESENSORH
#define CAPACITIVEMOISTURESENSORH
#include <Arduino.h>
#include <SoftwareSerial.h>

class CapacitiveMoistureSensor
{
  private:
	const uint8_t dPin;
	const uint8_t aPin;

  public:
	CapacitiveMoistureSensor(const uint8_t dPin, const uint8_t aPin);
	uint8_t read();

	uint8_t readPercent(uint16_t val);
};

#endif