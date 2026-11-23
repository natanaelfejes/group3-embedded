#pragma once
enum class Wifi_State {
    Connected,
    Disconnected,
    Connecting, 
    Failed
};


struct Wifi_Status {
    bool connected_to_wifi = false;
    Wifi_State current_state = Wifi_State::Disconnected; 
    Wifi_State previous_state = Wifi_State::Disconnected;
};