#include "stdio.h"
#include "hardware/gpio.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "lwip/apps/http_client.h"
#include <iostream>

err_t make_get_request(const char *server_name, int port, const char *uri);

int connect_to_wifi(bool* is_connecting_flag);