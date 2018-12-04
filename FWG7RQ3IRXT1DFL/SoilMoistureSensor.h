#ifndef SOILMOISTURESENSORH
#define SOILMOISTURESENSORH
#include <Arduino.h>
#include <SoftwareSerial.h>



class SoilMoistureSensor
{
  private:
	const uint8_t upper_pin_;
	const uint8_t lower_pin_;
	const uint8_t analog_pin_;

  public:
	SoilMoistureSensor(const uint8_t upperPin, const uint8_t lowerPin, const uint8_t analogPin);
	unsigned read();

	uint8_t readPercent();
};

#endif
