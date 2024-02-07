#include "devices.hpp"

bool Phone::get_wifi_connection(){
    return this->wifi_connection;
}

bool Phone::get_bluetooth_discoverable(){
    return this->bluetooth_discoverable;
}

void Phone::change_wifi_connection(bool val){
    this->wifi_connection = val;
}

void Phone::change_bluetooth_discoverable(bool val){
    this->bluetooth_discoverable = val;
}

int Phone::wifi_checker(){
    // need to add logic and implement functions from wifi library
    return 0;
}

int Phone::bluetooth_checker(){
    // need to add logic and implement functions from bluetooth library
    return 0;
}
