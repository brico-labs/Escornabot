// ButtonSetBluetooth.h
#ifndef _BUTTON_SET_BLUETOOTH
#define _BUTTON_SET_BLUETOOTH

#include "ButtonSet.h"
#include <Arduino.h>

// one-key comands: one character by line
const static char* KEY_PRESSED = "NESWGR";
const static char* KEY_RELEASED = "neswgr";

class ButtonSetBluetooth : ButtonSet
{
public:

    typedef struct {
        HardwareSerial* serial;
        uint32_t bauds;
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

    bool readCommand(char* buffer, size_t size);
};

#endif // _BUTTON_SET_BLUETOOTH

// EOF
