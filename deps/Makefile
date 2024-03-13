PCAP = PcapPlusPlus
TUYAPP = tuyapp
BUILD_DIR = build
LIB_DIR = lib


tuyapp_lib: $(TUYAPP)/src/tuyaAPI33.cpp
	mkdir -p $(BUILD_DIR)/tuya
	mkdir -p $(LIB_DIR)/tuya
	g++ -c $(TUYAPP)/src/tuyaAPI33.cpp -o $(BUILD_DIR)/tuya/tuyaAPI33.o
	ar rcs $(LIB_DIR)/tuya/libtuya.a $(BUILD_DIR)/tuya/tuyaAPI33.o

pcap_lib:
	mkdir -p $(BUILD_DIR)/pcap
	mkdir -p $(LIB_DIR)/pcap
	cmake -S $(PCAP) -B $(BUILD_DIR)/pcap
	cd $(BUILD_DIR)/pcap && make Pcap++ -j$(nproc)
	cp $(BUILD_DIR)/pcap/Common++/libCommon++.a $(LIB_DIR)/pcap
	cp $(BUILD_DIR)/pcap/Pcap++/libPcap++.a $(LIB_DIR)/pcap
	cp $(BUILD_DIR)/pcap/Packet++/libPacket++.a $(LIB_DIR)/pcap

libs:
	$(MAKE) tuyapp_lib
	$(MAKE) pcap_lib

.PHONY: clean
clean:
	rm -rf lib build
	
	