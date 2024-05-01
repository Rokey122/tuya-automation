#include "../header/light.hpp"

/*********
Bulb class
*********/

// constructor
Bulb::Bulb(std::string id, std::string key, std::string ip, int switch_led_code){
    this->id = id;
    this->key = key;
    this->ip = ip;
    this->switch_led_code = switch_led_code;
}

// return the bulbs ip
std::string Bulb::get_bulb_ip(){
    return this->ip;
}

// send on or off command to the bulb
void Bulb::on_off_switch(int state){
    std::stringstream payload;
    tuyaAPI33 tuya;
    unsigned char buffer[1024];
    unsigned char recv_buffer[1024];
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
    int command_len = tuya.BuildTuyaMessage(buffer, TUYA_CONTROL, payload.str(), this->key);

    int send = -1;
    int recv = -1;
    while (send < 0 || recv < 0){
	    if (tuya.ConnectToDevice(this->ip, PORT)){
            send = tuya.send(buffer, command_len);
            recv = tuya.receive(recv_buffer, 1023);
	        tuya.disconnect();
        }
        usleep(100);
    }
}

/***********
Lights class
***********/

// constructor
Lights::Lights(const std::vector<Bulb> &bulbs){
    this->bulbs = bulbs;
    this->state = 0;
}

std::vector<std::string> Lights::get_light_ip(){
    std::vector<std::string> bulb_ips;

    for(auto bulb : this->bulbs){
        bulb_ips.push_back(bulb.get_bulb_ip());
    }

    return bulb_ips;
}

// send on or off command to all the bulbs
void Lights::on_off_switch(int state){
    if (this->state != state){
        for(auto bulb : this->bulbs){
            bulb.on_off_switch(state);
        }
        this->state = state;
    }
}
