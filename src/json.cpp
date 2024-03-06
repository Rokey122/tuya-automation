#include "../header/json.hpp"
#include <iostream>

Phone jsonparse_phone(){
    std::fstream file("phone.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    std::string bluetooth_mac = value["bluetooth_mac"].asString();
    std::string wifi_mac = value["wifi_mac"].asString();

    file.close();

    Phone phone(bluetooth_mac, wifi_mac);

    return phone;
}

Lights jsonparse_lights(){
    std::fstream file("lights.json");
    Json::Value value;
    Json::Reader reader;

    reader.parse(file, value);

    std::vector<Bulb> bulbs;

    for (Json::Value::ArrayIndex i = 0; i != value.size(); i++){
        std::string id = value[i]["id"].asString();
        std::string key = value[i]["key"].asString();
        std::string ip = value[i]["ip"].asString();
        int switch_led_code = value[i]["switch_led_code"].asInt();

        Bulb bulb(id, key, ip, switch_led_code);

        bulbs.push_back(bulb);
    }

    Lights light(bulbs);

    return light;
}
