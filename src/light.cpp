#include "../header/light.hpp"

Bulb::Bulb(std::string id, std::string key, std::string ip, int switch_led_code){
    this->id = id;
    this->key = key;
    this->ip = ip;
    this->switch_led_code = switch_led_code;
}

void Bulb::on_off_switch(int state){
    std::stringstream payload;
    tuyaAPI33 *tuya = this->tuya;
    unsigned char buffer[1024];
    std::string bool_state;

    switch (state){
        case 0:
            bool_state = "false";
            break;
        case 1:
            bool_state = "true";
            break;
    }

    payload << "{\"devId\":\"" << this->id << "\",\"dps\":{\"" << this->switch_led_code << "\":" << bool_state << "}}";
    int command_len = tuya->BuildTuyaMessage(buffer, TUYA_CONTROL, payload.str(), this->key);
    tuya->ConnectToDevice(this->ip, PORT);
    tuya->send(buffer, command_len);
    tuya->disconnect();
}





Lights::Lights(const std::vector<Bulb> &bulbs){
    this->bulbs = bulbs;
}

int Lights::get_state(){
    return this->state;
}

void Lights::change_state(int val){
    this->state = val;
}

void Lights::on_off_switch(int state){
    for(auto bulb : this->bulbs){
        bulb.on_off_switch(state);
    }
    this->change_state(state);
}

