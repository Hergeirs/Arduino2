#include "SoilMoistureSensor.h"

SoilMoistureSensor::SoilMoistureSensor(const uint8_t upperPin, const uint8_t lowerPin, const uint8_t analogPin)
	: upper_pin_(upperPin), lower_pin_(lowerPin), analog_pin_(analogPin)
{
	pinMode(upperPin, OUTPUT);
	digitalWrite(upperPin, LOW);

	pinMode(lowerPin, OUTPUT);
	digitalWrite(lowerPin, LOW);
	pinMode(analogPin, INPUT);
}

unsigned SoilMoistureSensor::read()
{
	unsigned reading;
	// drive a current through the divider
	digitalWrite(upper_pin_, LOW);
	digitalWrite(lower_pin_, HIGH);
	// wait a moment for capacitance effects to kick in
	delay(1);
	// take a reading takes 100 microseconds to complete read.
	reading = analogRead(analog_pin_);

	// reverse the current
	digitalWrite(upper_pin_, HIGH);
	digitalWrite(lower_pin_, LOW);

	// 1 millisecond + 100 microseconds for analogRead

	delayMicroseconds(1100);

	// stop the current
	digitalWrite(upper_pin_, LOW);

	return reading;
}

uint8_t SoilMoistureSensor::readPercent()
{
	 /* 555 is the value for moisture in the air
	 // 288 is the value for when the sensor is submerged in water
	  then sett 555 to be 0%, 288 to be 100%, and map the percent between them */
	double valPercent = map (read(), 555, 280, 0, 100);
	//return (read() / 1023.0) * 100; // code for the previous sensor
	return (valPercent);
}