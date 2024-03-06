#include <string>
#include <sstream>
#include <vector>
#include "../deps/tuyapp/src/tuyaAPI33.hpp"

#ifndef LIGHTS
#define LIGHTS

#define PORT 6668

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
#endif