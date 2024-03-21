#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include "tuyaAPI33.hpp"

#ifndef LIGHTS
#define LIGHTS

#define PORT 6668

class Bulb{
    public:
        Bulb(std::string id, std::string key, std::string ip, int switch_led_code);

        std::string get_bulb_ip();

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

        std::vector<std::string> get_light_ip();

        void on_off_switch(int state);
    
    private:
        std::vector <Bulb> bulbs;
        int state;
};
#endif