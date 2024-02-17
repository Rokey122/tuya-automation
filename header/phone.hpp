#include <string>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

class Phone{
    public:
        Phone(std::string bluetooth_mac, std::string wifi_mac);
        ~Phone();
        
        bool get_wifi_connection();
        bool get_bluetooth_discoverable();
        void change_wifi_connection(int val);
        void change_bluetooth_discoverable(int val);

        int wifi_checker();
        int bluetooth_checker();


    private:
        int wifi_connection; // 0 is not connected to LAN, 1 is
        int bluetooth_discoverable; // 0 is not in proximity, 1 is
        bdaddr_t* bluetooth_mac;
        std::string wifi_mac;
        int dd;
};