// ButtonSet.h

#ifndef _BUTTON_SET_H
#define _BUTTON_SET_H

#include <stdint.h>

/**
 * Interface to different Vacaloura engines.
 */
class ButtonSet
{
public:

	enum
	{
		BUTTON_NONE = 0,
		BUTTON_UP = 1,
		BUTTON_RIGHT = 2,
		BUTTON_DOWN = 3,
		BUTTON_LEFT = 4,
		BUTTON_GO = 5,
		BUTTON_RESET = 6,
	};
    typedef uint8_t BUTTON;

	/**
	 * Does the hardware initialization.
	 */
	virtual void init() = 0;

	/**
	 * Scans the button input to test if anyone is pressed.
	 * @return The button being pressed.
	 */
	virtual BUTTON scanButtons() = 0;

};


#endif // _BUTTON_SET_H

// EOF
