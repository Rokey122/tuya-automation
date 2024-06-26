#include "light.hpp"
#include "phone.hpp"
#include "json.hpp"
#include "network.hpp"
#include <cstdlib>
#include <csignal>
#include <iostream>

bool terminated = false;

void signalHandler(int signal){
    terminated = true;
    std::exit(signal);
}

int main(){
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);

    bool bt = true;
    bool internet = true;

    int dd = hci_open_dev(hci_get_route(NULL));
    if (dd < 0){
        std::cout << "No bluetooth, continuing without bluetooth..." << std::endl;
        bt = false;
    }
    hci_close_dev(dd);

    std::string iface = get_interface();
    if (iface.size() == 0){
        std::cout << "No internet, continuing without internet..." << std::endl;
        internet = false;
    }

    if (!internet && !bt){
        std::cout << "Bluetooth and internet not discovered, cant continue." << std::endl;
        exit(0);
    }

    Phone phone = jsonparse_phone();
    Lights lights = jsonparse_lights();

    std::vector<std::string> hosts;
    start_host_discovery(&terminated, &hosts);

    std::vector<std::string> hosts_copy;

    sleep(5);
    int internet_state = 0;
    int bt_state = 0;

    int retries = 1;

    daemon(1, 0);

    while (true){
        for(int count = 0; count < retries; count++){
            if (bt){
                bt_state = phone.bluetooth_checker();
            }

            if (internet){
                mtx.lock();
                hosts_copy = hosts;
                mtx.unlock();

                internet_state = phone.multi_wifi_checker(hosts_copy, iface, lights.get_light_ip());
            }
            if ((internet_state == 1 || bt_state == 1) && 
                retries == 10){
                count = 0;
            }
        }
        if(internet_state == 1 || bt_state == 1){
            lights.on_off_switch(1);
            retries = 20;
        }
        else{
            lights.on_off_switch(0);
            retries = 1;
        }
        sleep(1);
        
    }

    terminated = true;
    return 0;
}