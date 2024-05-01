#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/l2cap.h>
#include <sys/socket.h>
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

        int wifi_checker(std::string ip, std::string iface);
        int multi_wifi_checker(std::vector<std::string> &hosts, std::string iface, std::vector<std::string> bulb_ips);

        int bluetooth_checker();

    private:
        struct sockaddr_l2 bluetooth_mac;
        std::string wifi_mac;

        double pcap_response = 0.0;
        pcpp::PcapLiveDevice *pcap_dev;
        pcpp::MacAddress pcap_source_mac;
        pcpp:: IPv4Address pcap_source_ip;
};
#endif