#include <string>
#include <sstream>
#include <vector>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include "../tuyapp/src/tuyaAPI33.hpp"

#define PORT 6668

class Phone{
    public:
        Phone(std::string bluetooth_mac, std::string wifi_mac);
        
        bool get_wifi_connection();
        bool get_bluetooth_discoverable();
        void change_wifi_connection(int val);
        void change_bluetooth_discoverable(int val);

        int wifi_checker();
        int bluetooth_checker();


    private:
        int wifi_connection; // 0 is not connected to LAN, 1 is
        int bluetooth_discoverable; // 0 is not in proximity, 1 is
        bdaddr_t* bluetooth_mac;
        std::string wifi_mac;
};

class Bulb{
    public:
        Bulb(std::string id, std::string key, std::string ip, int switch_led_code);

        void on_off_switch(int state);

    private:
        int switch_led_code;
        std::string id;
        std::string key;
        std::string ip;

};

class Lights{
    public:
        Lights(const std::vector<Bulb> &bulbs);

        void on_off_switch(int state);

        int get_state();
        void change_state(int val);
    
    private:
        std::vector <Bulb> bulbs;
        int state; // 0 is off, 1 is on
};