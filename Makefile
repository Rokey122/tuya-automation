INC = -Iheader
LIB = -Ldeps/lib

TUYAINC = -Ideps/tuyapp/src
TUYALIBS = -ltuya -lcrypto -lz -lssl

PCAPINC = -Ideps/PcapPlusPlus/Packet++/header -Ideps/PcapPlusPlus/Common++/header -Ideps/PcapPlusPlus/Pcap++/header 
PCAPLIBS = -lPcap++ -lPacket++ -lCommon++ -lpcap

BTLIBS = -lbluetooth
JSONLIBS = -ljsoncpp

PTHREADLIBS = -lpthread

BUILD = build

all: libs program

libs:
	cd deps && make tuyapp_lib && make pcap_lib

$(BUILD)/light.o: src/light.cpp header/light.hpp
	mkdir -p $(BUILD)
	g++ -c src/light.cpp $(INC) $(TUYAINC) -o $(BUILD)/light.o

$(BUILD)/phone.o: src/phone.cpp header/phone.hpp
	mkdir -p $(BUILD) 
	g++ -c src/phone.cpp $(INC) $(PCAPINC) -o $(BUILD)/phone.o

$(BUILD)/network.o: src/network.cpp header/network.hpp
	mkdir -p $(BUILD) 
	g++ -c src/network.cpp -o $(BUILD)/network.o

$(BUILD)/json.o: src/json.cpp header/json.hpp
	mkdir -p $(BUILD) 
	g++ -c src/json.cpp $(INC) $(PCAPINC) $(TUYAINC) -o $(BUILD)/json.o

$(BUILD)/main.o: src/main.cpp
	mkdir -p $(BUILD) 
	g++ -c src/main.cpp $(INC) $(PCAPINC) $(TUYAINC) -o $(BUILD)/main.o

$(BUILD)/tuya-automation: $(BUILD)/light.o $(BUILD)/phone.o $(BUILD)/network.o $(BUILD)/json.o $(BUILD)/main.o
	mkdir -p $(BUILD)
	g++ $(BUILD)/light.o $(BUILD)/phone.o $(BUILD)/network.o $(BUILD)/json.o $(BUILD)/main.o $(LIB)/tuya $(LIB)/pcap $(TUYALIBS) $(BTLIBS) $(JSONLIBS) $(PCAPLIBS) $(PTHREADLIBS) -o $(BUILD)/tuya-automation

program: $(BUILD)/tuya-automation

clean:
	rm -rf $(BUILD)
