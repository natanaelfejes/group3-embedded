#include "stdio.h"
#include <iostream>
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "pico/multicore.h"
#include "pico/status_led.h"
#include "wifi-connector.h"
#include "wifi-props.h"

constexpr uint LED_PIN = 7;
constexpr uint BUTTON_PIN = 10;
    

int main()
{
    Wifi_Status wifi_connection_status; 

    stdio_init_all();
   
    // Has to stay, to ensure the connector is alive
    if (cyw43_arch_init() != 0)
    {
        printf("Failed to connect \n");
        return 1;
    }
    cyw43_arch_enable_sta_mode();

    while (true) 
    { 
        int connect_to_wi_fi = poll_wifi_connector(wifi_connection_status);

        if(connect_to_wi_fi  == 1) 
        {
            return 1;
        }
        

        sleep_ms(200);
    }
}
 