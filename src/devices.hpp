class Phone{
    public:
        Phone(){
            wifi_connection = false;
            bluetooth_discoverable = false;
        }
        
        bool get_wifi_connection();
        bool get_bluetooth_discoverable();
        void change_wifi_connection(bool val);
        void change_bluetooth_discoverable(bool val);

        int wifi_checker();
        int bluetooth_checker();


    private:
        bool wifi_connection;
        bool bluetooth_discoverable;
};

class Bulb{
    public:
        Bulb();

        int get_state();
        void change_state(int val);

        void turn_on();
        void turn_off();

    private:
        int state;
};