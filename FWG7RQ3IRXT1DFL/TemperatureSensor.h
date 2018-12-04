#ifndef TEMPERATURESENSORH
#define TEMPERATURESENSORH
#include <Arduino.h>
#include <SoftwareSerial.h>


class TemperatureSensor
{
  private:
	const uint8_t triggerPin;
	const uint8_t readPin;

  public:
	TemperatureSensor(const uint8_t pinTrigger, const uint8_t readPin);

	const int8_t read();
};

#endif
