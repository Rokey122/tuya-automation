#include "../header/phone.hpp"

/*
Constructor and destructor
*/

// constructor
Phone::Phone(std::string bluetooth_mac_str, std::string wifi_mac){
    memset(&this->bluetooth_mac, 0, sizeof(this->bluetooth_mac));
    this->bluetooth_mac.l2_family = AF_BLUETOOTH;
    str2ba(bluetooth_mac_str.c_str(), &this->bluetooth_mac.l2_bdaddr);

    this->wifi_mac = wifi_mac;

    this->pcap_dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIpOrName(get_interface());
    this->pcap_source_mac = this->pcap_dev->getMacAddress();
    this->pcap_source_ip = this->pcap_dev->getIPv4Address();
}

// destructor
Phone::~Phone(){
}

/*
Internet functions
*/

// check is a device with the ip has the mac of the target phone
int Phone::wifi_checker(std::string ip, std::string iface){
    this->pcap_dev->open();
    pcpp::IPv4Address target_ip = pcpp::IPv4Address(ip);
    pcpp::MacAddress result = pcpp::NetworkUtils::getInstance().getMacAddress(target_ip, this->pcap_dev, this->pcap_response, this->pcap_source_mac, this->pcap_source_ip, 5);
    if (result == this->wifi_mac){
        this->pcap_dev->close();
        return 1;
    }
    else{
        this->pcap_dev->close();
        return 0;
    }
    this->pcap_dev->close();
    return -1;
}

// check multiple ip addresses and see if one of them is the target phone
int Phone::multi_wifi_checker(std::vector<std::string> &hosts, std::string iface, std::vector<std::string> bulb_ips){
    for (auto host : hosts){
        if (host.compare(get_ip()) != 0 && 
            std::find(bulb_ips.begin(), bulb_ips.end(), host) == bulb_ips.end() &&
            this->wifi_checker(host, iface) == 1){
            return 1;
        }
    }
    return 0;
}

/*
Bluetooth functions
*/

// see whether a phone is in bluetooth proximity or not
int Phone::bluetooth_checker(){
    int sock = socket(PF_BLUETOOTH, SOCK_RAW, BTPROTO_L2CAP);
 
    if (connect(sock, (struct sockaddr *) &this->bluetooth_mac, sizeof(this->bluetooth_mac)) < 0) {
		close(sock);
        return 0;
	}
    else {
        close(sock);
        return 1;
    }
    close(sock);
    return -1;
}