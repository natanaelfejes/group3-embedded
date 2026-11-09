#include "stdio.h"
#include "lwip/apps/http_client.h"
#include "pico/cyw43_arch.h"
#include "wifi-connector.h"
#include <iostream>


const char *WIFI_SSID = "SSID Here";
const char *WIFI_PASSWORD = "Password here";


int connect_to_wifi(bool* is_connecting_flag) {

    if (cyw43_arch_init() != 0)
    {
        printf("Failed to connect \n");
        return 1;
    }

    cyw43_arch_enable_sta_mode();
    std::cout << " Connecting to WIFI\n" << std::endl;

    *is_connecting_flag = true;

    int result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000);

    // result = -2 means Timeout Error
    if(result == -2) {
        std::cout << "Error, failed to connect - TIMEOUT ERROR " << std::endl;
        return 1;
    } 
    // result = -7 means Wrong Credentials
    if(result == -7) 
    {
        std::cout << "Error, failed to connect - WRONG CREDENTIALS \n" << std::endl;
        return 1;
    }
    // if result != 0 means the attempt failed
    if(result != 0) 
    {
        std::cout << "Failed to connect to internet %d" << result << std::endl;
        return 1;

    }
  

    std::cout << "Connected to WIFI" << std::endl;
    cyw43_arch_deinit();
    sleep_ms(30);
    return 0;
}