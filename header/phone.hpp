#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <thread>
#include "network.hpp"
#include "IpAddress.h"
#include "PcapLiveDevice.h"
#include "PcapLiveDeviceList.h"
#include "MacAddress.h"
#include "NetworkUtils.h"

#ifndef PHONE
#define PHONE
class Phone{
    public:
        Phone(std::string bluetooth_mac, std::string wifi_mac);
        ~Phone();
        
        bool get_wifi_connection();
        bool get_bluetooth_discoverable();
        void change_wifi_connection(int val);
        void change_bluetooth_discoverable(int val);

        int wifi_checker(std::string ip, std::string iface);
        int multi_wifi_checker(std::vector<std::string> &hosts, std::string iface);

        int bluetooth_checker();

    private:
        int wifi_connection; // 0 is not connected to LAN, 1 is
        int bluetooth_discoverable; // 0 is not in proximity, 1 is
        bdaddr_t *bluetooth_mac = new bdaddr_t;
        std::string wifi_mac;

        int dd;

        double pcap_response = 0.0;
        pcpp::PcapLiveDevice *pcap_dev;
        pcpp::MacAddress pcap_source_mac;
        pcpp:: IPv4Address pcap_source_ip;
};
#endif