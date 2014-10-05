// BluetoothInterface.h
/*

Copyright (C) 2014 Bricolabs - http://bricolabs.cc

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
USA.

See LICENSE.txt for details

*/

#ifndef _BLUETOOTH_INTERFACE_H
#define _BLUETOOTH_INTERFACE_H

#include "ButtonSet.h"
#include <Arduino.h>

// one-key comands: one character by line
const static char* BUTTONS_PRESSED = "NESWGR";
const static char* BUTTONS_RELEASED = "neswgr";

#define COMMAND_MAX_LENGTH 10

class BluetoothInterface : ButtonSet
{
public:

    typedef struct {
        HardwareSerial* serial;
        uint32_t bauds;
    } Config;

    /**
     * Constructor.
     */
    BluetoothInterface(const Config* cfg);

    ////////////////////////////////////////////////////////////
    // ButtonSet interface
    ////////////////////////////////////////////////////////////

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

    char command[COMMAND_MAX_LENGTH + 1];
    uint8_t command_idx = 0;

    bool readLine();

};

#endif // _BLUETOOTH_INTERFACE_H

// EOF
