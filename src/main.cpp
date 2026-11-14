#include <iostream>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "desk-height.h"

// ---- Wi-Fi: disabled for now, the button on GP10 is used for the desk height instead ----
// #include "pico/cyw43_arch.h"
// #include "pico/multicore.h"
// #include "pico/status_led.h"
// #include "wifi-connector.h"
// #include <atomic>
//
// constexpr uint LED_PIN = 7;
// constexpr uint BUTTON_PIN = 10;
//
// struct ButtonState 
// {
//     bool ButtonPressed = false;
//     bool ButtonPreviousState = false;
// };
//
// ButtonState button_state; 
//
// bool currently_connecting_to_wifi = false;
// bool start_connect_to_wifi = false;
// std::atomic<bool> is_connected_to_wifi{false};
//
// // Used to provide visual feedback with the LED pin, when connection to wi-fi is initiated or completed.
// void signal_connecting_to_wifi() 
// {
//     int sleep_delay = is_connected_to_wifi ? 0 : 150;
//
//     while(true) 
//     {
//         gpio_put(LED_PIN, currently_connecting_to_wifi);
//         sleep_ms(sleep_delay);
//         gpio_put(LED_PIN, is_connected_to_wifi);
//
//         sleep_ms(200);
//     }
// }
//
// // Button interupt service routine - mainly prevents the button to call multiple times, after the initial press. 
// void button_isr(uint gpio, uint32_t events)
// {
//     if(gpio != BUTTON_PIN || (events & GPIO_IRQ_EDGE_RISE) == 0u) 
//     {
//         return;
//     }
//
//     if(!button_state.ButtonPressed && !button_state.ButtonPreviousState)
//     {
//         button_state.ButtonPressed = true;
//         button_state.ButtonPreviousState = true;
//     }
// }
// ------------------------------------------------------------------------------------------

int main()
{
    stdio_init_all();

    // ---- Wi-Fi: disabled ----
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, false);
    //
    // gpio_init(BUTTON_PIN);
    // gpio_set_dir(BUTTON_PIN, GPIO_IN);
    // gpio_pull_down(BUTTON_PIN);
    // gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_RISE, true, &button_isr);
    // -------------------------

    // Potentiometer (desk height) and the return-to-original button on GP10
    desk_height_init();

    // ---- Wi-Fi: disabled ----
    // multicore_launch_core1(signal_connecting_to_wifi);
    // -------------------------
    std::cout << "Turn the knob to set the desired position, press the button to return to the original \n" << std::endl;

    while (true) 
    {   
        desk_height_update();

        // ---- Wi-Fi: disabled ----
        // gpio_put(LED_PIN, gpio_get(BUTTON_PIN));
        // start_connect_to_wifi = gpio_get(BUTTON_PIN);
        //
        // if(button_state.ButtonPressed) 
        // {
        //     if(!is_connected_to_wifi) 
        //     {
        //         if(start_connect_to_wifi) 
        //         {
        //             is_connected_to_wifi = !connect_to_wifi(&currently_connecting_to_wifi);
        //             start_connect_to_wifi = !start_connect_to_wifi;
        //         }
        //     }
        //     button_state.ButtonPressed = false;
        // }
        //
        // button_state.ButtonPreviousState = false;
        // -------------------------

        sleep_ms(50);
    }
}
