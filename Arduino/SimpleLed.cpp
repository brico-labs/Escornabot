// SimpleLed.cpp

#include "SimpleLed.h"
#include <Arduino.h>

SimpleLed::SimpleLed(uint8_t pin)
{
	this->_pin = pin;
}


void SimpleLed::init()
{
	_status = false;
	pinMode(_pin, OUTPUT);
}

void SimpleLed::setStatus(bool value)
{
	this->_status = value;
	digitalWrite(_pin, _status ? HIGH : LOW);
}

void SimpleLed::toggle()
{
	_status = !_status;
	digitalWrite(_pin, _status ? HIGH : LOW);
}


// EOF
