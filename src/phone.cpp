#include "devices.hpp"

Phone::Phone(std::string bluetooth_mac, std::string wifi_mac){
    this->wifi_connection = 0;
    this->bluetooth_discoverable = 0;
    str2ba(bluetooth_mac.c_str(), this->bluetooth_mac);
    this->wifi_mac = wifi_mac;
}

bool Phone::get_wifi_connection(){
    return this->wifi_connection;
}

bool Phone::get_bluetooth_discoverable(){
    return this->bluetooth_discoverable;
}

void Phone::change_wifi_connection(int val){
    this->wifi_connection = val;
}

void Phone::change_bluetooth_discoverable(int val){
    this->bluetooth_discoverable = val;
}

int Phone::wifi_checker(){
    // need to add logic and implement functions from wifi library
    return 0;
}

int Phone::bluetooth_checker(){
    int dd = hci_open_dev(hci_get_route(NULL));

    // see whether a phone is in bluetooth proximity or not
    if (hci_read_remote_name(dd, this->bluetooth_mac, 0, NULL, 25000) == 0){
        if (this->bluetooth_discoverable != 1){this->bluetooth_discoverable = 1;}
        return 1;
    }
    else{
        if (this->bluetooth_discoverable != 0){this->bluetooth_discoverable = 0;}
        return 0;
    }
}
