// ButtonSetBluetooth.cpp

#include "ButtonSetBluetooth.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

ButtonSetBluetooth::ButtonSetBluetooth(const Config* cfg)
{
    _config = cfg;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

void ButtonSetBluetooth::init()
{
    _config->serial->begin(_config->bauds, SERIAL_8N1);
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

ButtonSet::BUTTON ButtonSetBluetooth::scanButtons()
{
    char command[10];

    while (readCommand(command, 10))
    {
        // one-char commands
        if (strlen(command) == 1)
        {
            char* found = strchr(KEY_RELEASED, command[0]);
            if (found)
            {
                return (BUTTON)((found - KEY_RELEASED) + 1);
            }
        }
    }

    return BUTTON_NONE;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

bool ButtonSetBluetooth::readCommand(char* buffer, size_t size)
{
    uint8_t tries = 10; // timeout 100 (10*delay) ms
    while (tries-- > 0)
    {
        while (_config->serial->available())
        {
            if (size-- <= 0) return false;

            char key = _config->serial->read();

            if (key == '\n')
            {
                *buffer = '\0';
                return true;
            }

            *buffer = key;
            buffer++;

            delay(10); // 100 (1000/10) chars by second
        }
    }

    return false;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

// EOF
