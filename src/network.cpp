#include "../header/network.hpp"
std::mutex mtx;

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

std::string get_ip_base(){
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

void online_devices(std::string ip, std::vector<std::string> *hosts, bool *terminated){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in sockaddr;
    sockaddr.sin_port = htons(80);
    sockaddr.sin_family = AF_INET;
    inet_pton(AF_INET, ip.c_str(), &sockaddr.sin_addr);

    while (!*terminated){
        connect(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr));

        if (errno == 111 && std::find(hosts->begin(), hosts->end(), ip) == hosts->end()){
            mtx.lock();
            hosts->push_back(ip);
            mtx.unlock();
        }
        if (errno != 111 && std::find(hosts->begin(), hosts->end(), ip) != hosts->end()){
            mtx.lock();
            hosts->erase(std::find(hosts->begin(), hosts->end(), ip));
            mtx.unlock();
        }
        
        sleep(2);
    }
}


void start_host_discovery(bool *terminated, std::vector<std::string> *hosts){
    std::string ip_base = get_ip_base();
    for (int num = 0; num < 256; num++){
        std::thread t(online_devices, ip_base + std::to_string(num), hosts, terminated);
        t.detach();
    }
}

void stop_host_discovery(bool *terminated){
    *terminated = true;
}

