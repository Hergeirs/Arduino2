#ifndef CAPACITIVEMOISTURESENSORH
#define CAPACITIVEMOISTURESENSORH
#include <Arduino.h>
class CapacitiveMoistureSensor
{
  private:
	const uint8_t pin;

  public:
	CapacitiveMoistureSensor(const uint8_t pPin);
	unsigned read();

	uint8_t readPercent(double val);
};

#endif