#include "../header/phone.hpp"

Phone::Phone(std::string bluetooth_mac_str, std::string wifi_mac){
    this->wifi_connection = 0;
    this->bluetooth_discoverable = 0;
    str2ba(bluetooth_mac_str.c_str(), this->bluetooth_mac);
    this->wifi_mac = wifi_mac;
    this->dd = hci_open_dev(hci_get_route(NULL));

    this->pcap_dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIpOrName(get_interface());
    this->pcap_source_mac = this->pcap_dev->getMacAddress();
    this->pcap_source_ip = this->pcap_dev->getIPv4Address();
}

Phone::~Phone(){
    hci_close_dev(this->dd);
    delete this->bluetooth_mac;
}

bool Phone::get_wifi_connection(){
    return this->wifi_connection;
}

bool Phone::get_bluetooth_discoverable(){
    return this->bluetooth_discoverable;
}

void Phone::change_wifi_connection(int val){
    this->wifi_connection = val;
}

void Phone::change_bluetooth_discoverable(int val){
    this->bluetooth_discoverable = val;
}

int Phone::wifi_checker(std::string ip, std::string iface){
    this->pcap_dev->open();
    pcpp::IPv4Address target_ip = pcpp::IPv4Address(ip);
    pcpp::MacAddress result = pcpp::NetworkUtils::getInstance().getMacAddress(target_ip, this->pcap_dev, this->pcap_response, this->pcap_source_mac, this->pcap_source_ip, this->pcap_timeout);

    if (result == this->wifi_mac){
        if (this->wifi_connection != 1){this->wifi_connection = 1;}
        this->pcap_dev->close();
        return 1;
    }
    else{
        if (this->wifi_connection != 0){this->wifi_connection = 0;}
        this->pcap_dev->close();
        return 0;
    }
    this->pcap_dev->close();
    return -1;
}

int Phone::bluetooth_checker(){
    int &dd = this->dd;

    // see whether a phone is in bluetooth proximity or not
    if (hci_read_remote_name(dd, this->bluetooth_mac, 0, NULL, 25000) == 0){
        if (this->bluetooth_discoverable != 1){this->bluetooth_discoverable = 1;}
        return 1;
    }
    else{
        if (this->bluetooth_discoverable != 0){this->bluetooth_discoverable = 0;}
        return 0;
    }
    return -1;
}