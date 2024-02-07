#include <string>
#include <sstream>
#include <vector>
#include "../tuyapp/src/tuyaAPI33.hpp"

#define PORT 6668

class Phone{
    public:
        Phone(){
            wifi_connection = false;
            bluetooth_discoverable = false;
        }
        
        bool get_wifi_connection();
        bool get_bluetooth_discoverable();
        void change_wifi_connection(bool val);
        void change_bluetooth_discoverable(bool val);

        int wifi_checker();
        int bluetooth_checker();


    private:
        bool wifi_connection;
        bool bluetooth_discoverable;
};

class Bulb{
    public:
        Bulb(std::string id, std::string key, std::string ip, int switch_led_code);

        int get_state();
        void change_state(int val);

        void on_off_switch(int state);

    private:
        int switch_led_code;
        std::string id;
        std::string key;
        std::string ip;

};

class Lights{
    public:
        Lights(std::vector<Bulb> bulbs);

        void on_off_switch(int state);

        int get_state();
        void change_state(int val);
    
    private:
        std::vector <Bulb> bulbs;
        int state;
};