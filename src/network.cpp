#include "../header/network.hpp"

std::string get_interface(){
    struct ifaddrs *ifaddrs;
    std::string ifa_name;
    getifaddrs(&ifaddrs);

    for(struct ifaddrs *addrs = ifaddrs; addrs != nullptr; addrs = addrs->ifa_next){
        if(addrs->ifa_addr && addrs->ifa_addr->sa_family == AF_INET && (std::string)addrs->ifa_name != (std::string)"lo"){
            ifa_name = addrs->ifa_name;
            freeifaddrs(ifaddrs);
            break;
        }
    }
    return ifa_name;
}

std::string get_ip(){
    struct ifaddrs *ifaddrs;
    struct sockaddr_in *sockaddr;
    std::string ifa_addr;
    getifaddrs(&ifaddrs);

    for(struct ifaddrs *addrs = ifaddrs; addrs != nullptr; addrs = addrs->ifa_next){
        if(addrs->ifa_addr && addrs->ifa_addr->sa_family == AF_INET && (std::string)addrs->ifa_name != (std::string)"lo"){
            sockaddr = (struct sockaddr_in*) addrs->ifa_addr;
            ifa_addr = inet_ntoa(sockaddr->sin_addr);
            freeifaddrs(ifaddrs);
            break;
        }
    }

    int position = ifa_addr.find_last_of(".") + 1;
    ifa_addr.erase(position);
    return ifa_addr;
}  

