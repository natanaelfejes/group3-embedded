#include "desk-height.h"

#include <cstdlib>
#include <iomanip>
#include <iostream>

#include "hardware/adc.h"
#include "pico/stdlib.h"

namespace
{
    //Dropping 3 bits for noise reduction
    constexpr int DROPPED_BITS = 3;
    constexpr int LEVEL_MAX = (4096 >> DROPPED_BITS) - 1; // 511
   
    // if the difference between current status and desired is under this number, the desk doesnt move
    constexpr int ERROR_LEVEL = 2;  

    int original_level = 0; // knob level at power-on
    int desired_level = 0;  // what the knob or the return button last asked for
    bool button_was_pressed = false;

    // Knob position as a 9-bit level, 0..LEVEL_MAX.
    int read_pot_level()
    {
        return adc_read() >> DROPPED_BITS;
    }

    float as_fraction(int level)
    {
        return static_cast<float>(level) / LEVEL_MAX;
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

    desired_level = original_level;
    std::cout << "Original position: " << as_fraction(original_level) << std::endl;
}

void desk_height_update()
{
    // Knob turned 
    const int level = read_pot_level();
    if (std::abs(level - desired_level) > ERROR_LEVEL)
    {
        desired_level = level;
        std::cout << "Desired position: " << as_fraction(desired_level) << std::endl;
    }

    // Return button pressed
    const bool pressed = gpio_get(RETURN_BUTTON_PIN);
    if (pressed && !button_was_pressed)
    {
        desired_level = original_level;
        std::cout << "Returning to original position: " << as_fraction(desired_level) << " (original)" << std::endl;
    }
    button_was_pressed = pressed;
}

float desk_desired_position()
{
    return as_fraction(desired_level);
}
