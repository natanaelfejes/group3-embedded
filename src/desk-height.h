#ifndef DESK_HEIGHT_H
#define DESK_HEIGHT_H

#include "pico/types.h"

// Desk height simulated with a potentiometer, printed as 0.0 .. 1.0.
// Turning the knob sets the desired position. Pressing the return button
// sets it back to the saved position.

constexpr uint POT_PIN = 26;           // GP26 = ADC input 0
constexpr uint POT_ADC_INPUT = 0;
constexpr uint RETURN_BUTTON_PIN = 10; // 3V3 -> button -> pin, pull-down inside the Pico

void desk_height_init();  
void desk_height_update();
float get_desk_desired_position(); // 0.0 .. 1.0

#endif 
