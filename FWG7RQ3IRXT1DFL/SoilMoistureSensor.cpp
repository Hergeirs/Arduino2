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
  Serial.println("Reading shit YOH");
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
	return (read() / 1023.0) * 100;
}
