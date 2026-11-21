#include "desk-height.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "hardware/adc.h"
#include "pico/stdlib.h"

namespace
{
    //Dropping 3 bits for noise reduction
    constexpr int DROPPED_BITS = 5;
    constexpr int LEVEL_MAX = (4096 >> DROPPED_BITS) - 1; // highest level after dropping bits
   
    // if the difference between current status and desired is under this number, the desk doesnt move
    constexpr int ERROR_LEVEL = 2;  

    float saved_position = 0.0f; // 0.0 .. 1.0, converted to a level when used
    int desired_level = 0;      
    int last_knob_level = 0;    
    bool button_was_pressed = false;

    float as_fraction(int level)
    {
        return static_cast<float>(level) / LEVEL_MAX;
    }

    int as_level(float position)
    {
        return static_cast<int>(position * LEVEL_MAX + 0.5f);
    }
}

void desk_height_init()
{
    adc_init();
    adc_gpio_init(POT_PIN);
    adc_select_input(POT_ADC_INPUT);

    gpio_init(RETURN_BUTTON_PIN);
    gpio_set_dir(RETURN_BUTTON_PIN, GPIO_IN);
    gpio_pull_down(RETURN_BUTTON_PIN);

    // Print positions as 0.000 .. 1.000.
    std::cout << std::fixed << std::setprecision(3);

    desired_level = as_level(saved_position);
    std::cout << "Saved position: " << saved_position * 100 << "%" << std::endl;
}

void desk_height_update()
{
    // Knob turned 
    const int raw = adc_read();              // 12-bit, 0..4095
    const int level = raw >> DROPPED_BITS;   // 7-bit, 0..LEVEL_MAX
    if (std::abs(level - last_knob_level) > ERROR_LEVEL)
    {
        last_knob_level = level;
        desired_level = level;
        std::cout << "Desired position: " << as_fraction(desired_level) * 100<< "%"
                  << "  (raw: " << raw << ", level - "<<DROPPED_BITS<<" bits dropped " << level << ")" << std::endl;
    }

    // Return button pressed
    const bool pressed = gpio_get(RETURN_BUTTON_PIN);
    if (pressed && !button_was_pressed)
    {
        desired_level = as_level(saved_position);
        std::cout << "Returning to saved position: " << as_fraction(desired_level) * 100 << "%"
                  << "  (saved " << saved_position << ", level " << desired_level << ")" << std::endl;
    }
    button_was_pressed = pressed;
}

float get_desk_desired_position()
{
    return as_fraction(desired_level);
}
