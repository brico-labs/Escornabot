// Escornabot.h
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

#ifndef _ESCORNABOT_H
#define _ESCORNABOT_H

#include <Arduino.h>
#include "Configuration.h"
#include "MoveProgram.h"
#include "Engine.h"
#include "ButtonSet.h"
#include "StatusIndicator.h"

// motor engine defined from configuration
#ifdef ENGINE_TYPE_HBRIDGE

    #include "EngineHBridge.h"
    static const EngineHBridge::Config ENGINE_CONFIG = {
        motor_left_a: HBRIDGE_MOTOR_LEFT_A,
        motor_left_b: HBRIDGE_MOTOR_LEFT_B,
        motor_left_en: HBRIDGE_MOTOR_LEFT_EN,
        motor_right_a: HBRIDGE_MOTOR_RIGHT_A,
        motor_right_b: HBRIDGE_MOTOR_RIGHT_B,
        motor_right_en: HBRIDGE_MOTOR_RIGHT_EN,
        step_millis: HBRIDGE_STEP_MILLIS,
        turn_millis: HBRIDGE_TURN_MILLIS,
    };
    static EngineHBridge ENGINE_INSTANCE (&ENGINE_CONFIG);

#else ifdef ENGINE_TYPE_STEPPERS

    #include "EngineSteppers.h"
    static const EngineSteppers::Config ENGINE_CONFIG = {
        motor_left_in1: STEPPERS_MOTOR_LEFT_IN1,
        motor_left_in2: STEPPERS_MOTOR_LEFT_IN2,
        motor_left_in3: STEPPERS_MOTOR_LEFT_IN3,
        motor_left_in4: STEPPERS_MOTOR_LEFT_IN4,
        motor_right_in1: STEPPERS_MOTOR_RIGHT_IN1,
        motor_right_in2: STEPPERS_MOTOR_RIGHT_IN2,
        motor_right_in3: STEPPERS_MOTOR_RIGHT_IN3,
        motor_right_in4: STEPPERS_MOTOR_RIGHT_IN4,
        steps_per_second: STEPPERS_STEPS_PER_SECOND,
        line_steps: STEPPERS_LINE_STEPS,
        turn_steps: STEPPERS_TURN_STEPS,
    };
    static EngineSteppers ENGINE_INSTANCE (&ENGINE_CONFIG);

#endif

// Digital button set
#if defined(BUTTONS_DIGITAL)

    #include "ButtonSetDigital.h"
    static const ButtonSetDigital::Config BS_CONFIG = {
        pin_button_up: BS_DIGITAL_UP,
        pin_button_right: BS_DIGITAL_RIGHT,
        pin_button_down: BS_DIGITAL_DOWN,
        pin_button_left: BS_DIGITAL_LEFT,
        pin_button_go: BS_DIGITAL_GO,
        pin_button_reset: BS_DIGITAL_RESET,
    };
    static ButtonSetDigital BUTTONS_INSTANCE (&BS_CONFIG);

#elif defined(BUTTONS_ANALOG)

    #include "ButtonSetAnalog.h"
    static const ButtonSetAnalog::Config BS_CONFIG = {
        pin_button_set: BS_ANALOG_PIN,
        value_button_up: BS_ANALOG_VALUE_UP,
        value_button_right: BS_ANALOG_VALUE_RIGHT,
        value_button_down: BS_ANALOG_VALUE_DOWN,
        value_button_left: BS_ANALOG_VALUE_LEFT,
        value_button_go: BS_ANALOG_VALUE_GO,
        value_button_reset: BS_ANALOG_VALUE_RESET,
    };
    static ButtonSetAnalog BUTTONS_INSTANCE (&BS_CONFIG);

#elif defined(BUTTONS_BLUETOOTH)

    #include "BluetoothInterface.h"
    static const BluetoothInterface::Config BS_CONFIG = {
        serial: &(BS_BLUETOOTH_SERIAL),
        bauds: BS_BLUETOOTH_BAUDS,
    };
    static BluetoothInterface BUTTONS_INSTANCE (&BS_CONFIG);

    #define INDICATOR_INSTANCE BUTTONS_INSTANCE

#endif // Button set


///// global vars

#ifdef INDICATOR_INSTANCE
    static StatusIndicator* INDICATOR = &INDICATOR_INSTANCE;
#else
    static StatusIndicator* INDICATOR = NULL;
#endif

// engine
static Engine* ENGINE = (Engine*) &ENGINE_INSTANCE;

// button set
static ButtonSet* BUTTONS = (ButtonSet*) &BUTTONS_INSTANCE;

// program
static MoveProgram PROGRAM_INSTANCE;
static MoveProgram* PROGRAM = &PROGRAM_INSTANCE;


#endif // _ESCORNABOT_H

// EOF
