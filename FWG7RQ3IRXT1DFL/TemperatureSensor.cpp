#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(const uint8_t pinTrigger, const uint8_t readPin)
	:  triggerPin(pinTrigger), readPin(readPin)
{
	pinMode(triggerPin, OUTPUT);
	pinMode(readPin, INPUT);
	digitalWrite(triggerPin, HIGH);
}

int8_t TemperatureSensor::TemperatureSensor::read()
{
  Serial.println("Reading TEmp YOH");
	digitalWrite(triggerPin, HIGH);
  delay(1000);	
  uint16_t reading = analogRead(readPin);
	digitalWrite(triggerPin, LOW);
	// converting that reading to voltage, for 3.3v arduino use 3.3
	double voltage = reading * 5.0; // * 0.0009775171;
	voltage /= 1024.0;
	return round((voltage - 0.5) * 100);
}
