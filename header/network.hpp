#include <ifaddrs.h>
#include <string>
#include <arpa/inet.h>
#include <vector>
#include <cstdbool>
#include <algorithm>
#include <unistd.h>
#include <mutex>
#include <thread>

std::string get_interface();
std::string get_ip_base();

void online_devices(std::string ip, std::vector<std::string> *hosts, bool *terminated);
void start_host_discovery(bool *terminated, std::vector<std::string> *hosts);

extern std::mutex mtx;

