#include "stdio.h"
#include "lwip/apps/http_client.h"
#include "pico/cyw43_arch.h"
#include "wifi-connector.h"
#include "wifi-props.h"
#include <iostream>
#include "pico/stdlib.h"
#include "pico/stdlib.h"

const char *SERVER_NAME = "192.168.1.46";
const char *URI = "/api/v2/E9Y2LxT4g1hQZ7aD8nR3mWx5P0qK6pV7/desks";
const int PORT = 8000;

const char *WIFI_SSID = "ssid here";
const char *WIFI_PASSWORD = "pass here";


constexpr uint32_t WIFI_PRESISTENCE_CHECK_INTERVAL_MS = 2000; // must stay
constexpr uint32_t WIFI_RETRY_INTERVAL_MS = 5000; // must stay

constexpr uint MAX_WIFI_RETRIES = 5;
int used_wifi_recconection_retries = 0;


bool deadline_reached(absolute_time_t deadline) {
    return absolute_time_diff_us(
        get_absolute_time(), deadline
    ) <= 0;
}

//curently not in use will be used later
static err_t http_recv(void* arg, struct altcp_pcb* pcb, struct pbuf* p, err_t err)
{
    if (p == nullptr)
        return ERR_OK;

    // p contains received response-body data
    for (struct pbuf* current = p;
         current != nullptr;
         current = current->next)
    {
        printf("%.*s",
            (int)current->len,
            (char*)current->payload);
    }

   //connection_ok = true;

    pbuf_free(p);

    return ERR_OK;
}

// Currently not in use, will be used later
err_t make_get_request(const char *server_name, int port, const char *uri)
{
    static const httpc_connection_t settings = {};

    return httpc_get_file_dns(
        server_name,
        port,
        uri,
        &settings,
        http_recv,
        nullptr,
        nullptr
    );
}

int connect_to_wifi(Wifi_State* connection_status_flag) 
{

    std::cout << " Connecting to WIFI\n" << std::endl;

    *connection_status_flag = Wifi_State::Connecting;

    int result = cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 20000);
 
    // if result != 0 means the attempt failed
    if(result != 0) 
    {
        *connection_status_flag = Wifi_State::Failed;
        std::cout << "Failed to connect to internet %d" << result << std::endl;

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

      return 1;

    }
    
    *connection_status_flag = Wifi_State::Connected;

    std::cout << "Connected to WIFI" << std::endl;
    cyw43_arch_deinit();
    sleep_ms(30);
    return 0;
}

// Used to check the wifi presistence, by testinf the wifi link status
void check_wifi_presistence(Wifi_State* connection_status_flag) 
{
    std::cout << "Started wifi presistence test" << std::endl;
    int wifi_presistence_status = cyw43_wifi_link_status(&cyw43_state, CYW43_ITF_STA);

    std::cout << "After wifi presistence check: ";
    if(wifi_presistence_status == 0) 
    {
        std::cout << "Disconnected from Wi-fi" << std::endl;
        *connection_status_flag = Wifi_State::Disconnected;
    }

    if(wifi_presistence_status == 1) 
    {
        std::cout << "Connected to Wi-fi" << std::endl;
        *connection_status_flag = Wifi_State::Connected;
    }

    if(wifi_presistence_status == 2) 
    {
       std::cout << "Connected to Wi-Fi, but no IP address" << std::endl;
       *connection_status_flag = Wifi_State::Connected; 
    } 

    if(wifi_presistence_status == -1) 
    {
        *connection_status_flag = Wifi_State::Failed;
    }
}

absolute_time_t next_wifi_presistence_check = get_absolute_time();
absolute_time_t next_retry = get_absolute_time();

//Only this method shold be called anywhere else to establish the connection
int poll_wifi_connector(Wifi_Status& wifi_connection_status) 
{
        std::printf("%d \n" ,wifi_connection_status.current_state);
      
        if(wifi_connection_status.current_state == Wifi_State::Connected) 
        {
            if(deadline_reached(next_wifi_presistence_check))
            {

                check_wifi_presistence(&wifi_connection_status.current_state);
                next_wifi_presistence_check = make_timeout_time_ms(WIFI_PRESISTENCE_CHECK_INTERVAL_MS);
            }
        }

        if(wifi_connection_status.current_state != Wifi_State::Connected && deadline_reached(next_retry)) 
        {
            if(used_wifi_recconection_retries > MAX_WIFI_RETRIES) 
            {
                std::cout << "Failed to connect too many times. Exiting application" << std::endl;
                return 1;
            }

            std::cout << "Started Connecting to Wifi" << std::endl;
            wifi_connection_status.connected_to_wifi = !connect_to_wifi(&wifi_connection_status.current_state);

            next_wifi_presistence_check = make_timeout_time_ms(
                WIFI_PRESISTENCE_CHECK_INTERVAL_MS
            );

            next_retry = make_timeout_time_ms(
                WIFI_RETRY_INTERVAL_MS
            );

            if(wifi_connection_status.current_state == Wifi_State::Failed) 
            {
                used_wifi_recconection_retries += 1; 
            }
        }

        return 0;
}