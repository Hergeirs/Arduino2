#include "CapacitiveMoistureSensor.h"

CapacitiveMoistureSensor::CapacitiveMoistureSensor(const uint8_t dPin, const uint8_t aPin) : dPin(dPin), aPin(aPin)
{
    digitalWrite(dPin, HIGH);
}

uint8_t CapacitiveMoistureSensor::readPercent(uint16_t val)
{
     /* 555 is the value for moisture in the air
	 // 288 is the value for when the sensor is submerged in water
	  then sett 555 to be 0%, 288 to be 100%, and map the percent between them */
	Serial.print("val = ");
	Serial.println(val);
	val = constrain(val,280,555);
	double valPercent = map (val, 555, 280, 0, 100);
	//return (read() / 1023.0) * 100; // code for the previous sensor

	Serial.print("valpercent = ");
	Serial.println(valPercent);
	return valPercent;
}

uint8_t CapacitiveMoistureSensor::read()
{
	Serial.println("Reading SOIL YOH");
	digitalWrite(dPin,HIGH);
	delay(1000);
    uint16_t val = analogRead(aPin);
	digitalWrite(dPin,LOW);
    return readPercent(val);
}
