#include "CapacitiveMoistureSensor.h"

CapacitiveMoistureSensor::CapacitiveMoistureSensor(uint8_t pPin) : pin(pPin)
{
    digitalWrite(pPin, LOW);
}

uint8_t CapacitiveMoistureSensor::readPercent(double val)
{
     /* 555 is the value for moisture in the air
	 // 288 is the value for when the sensor is submerged in water
	  then sett 555 to be 0%, 288 to be 100%, and map the percent between them */
	double valPercent = map (read(), 555, 280, 0, 100);
	//return (read() / 1023.0) * 100; // code for the previous sensor
	return (valPercent);
}

unsigned CapacitiveMoistureSensor::read()
{
    double val = analogRead(pin);

    return readPercent(val);
}