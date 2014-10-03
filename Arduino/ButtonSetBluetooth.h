// ButtonSetBluetooth.h

#ifndef _BUTTON_SET_BLUETOOTH
#define _BUTTON_SET_BLUETOOTH

#include "ButtonSet.h"
#include <Arduino.h>

const static char* KEY_MAPPING = "_NESWGR";

class ButtonSetBluetooth : ButtonSet
{
public:

	typedef struct {
		HardwareSerial* serial;
	} Config;

	/**
	 * Constructor.
	 */
	ButtonSetBluetooth(const Config* cfg);

	/**
	 * Does the hardware initialization.
	 */
	virtual void init();

	/**
	 * Reads the buttons
	 * @return The button being pressed.
	 */
	virtual BUTTON scanButtons();

private:

	const Config* _config;
};

#endif // _BUTTON_SET_BLUETOOTH

// EOF
