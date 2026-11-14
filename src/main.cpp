#include <iostream>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "desk-height.h"

int main()
{
    stdio_init_all();

    // Potentiometer (desk height) and the return-to-original button on GP10
    desk_height_init();

    std::cout << "Turn the knob to set the desired position, press the button to return to the original \n" << std::endl;

    while (true) 
    {   
        desk_height_update();

        sleep_ms(50);
    }
}
