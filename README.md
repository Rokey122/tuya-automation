This program uses L2CAP protocol and arp ping function from the PcapPlusPlus library to send on/off commands to tuya devices when your phone is connected to wifi or near bluetooth proximity, using the tuyapp library. It is recommended to use on a raspberry pi device.

## Set up

### Getting tuya codes
Follow the tutorial on this link, and take note of your device id, local key, ip and dp_id for switch: https://www.youtube.com/watch?v=Q1ZShFJDvE0
Also, make sure to set a static ip address in your router settings to your devices so that they don't change their ips.
Write this codes in a json file under the name lights.json, using the lights_example.json file

### Building
You will need to build this on your target device, as cross compiling isn't possible. If building on a raspberry pi, I recommend the following:
1. Download your rpi's system image from their site, the one that you will also use on your rpi.
2. Mount the img file (will possibly need to use losetup to mount it as it has 2 partitions, boot and root, also will possibly have to enlarge that img file so that it has more space on it to write)
3. After mounting, chroot into it: https://gist.github.com/htruong/7df502fb60268eeee5bca21ef3e436eb
4. Copy/clone the repo to the home directory of the raspi root on your pc
5. Cd into repo and run "build program"

### Running
After building copy the tuya_automation file from build directory to your target system, along with lights.json and phone.json. Create a phone.json file using the example and put in your mac addresses. Json files and tuya_automation must be in the same folder. Run the program with ./tuya_automation, it will start and wait 5 seconds and then detach from the terminal and daemonize itself. Stop it by finding out its PID and killing the process.

## Dependencies
Must have libbluetooth-dev, libz-dev, libssl-dev, libpcap-dev, libjsoncpp-dev, libpthread-dev installed on target system, and rootfs where it is built.

## Known issues
For some reason, bluetooth stops working on the rpi zero w after trying to connect to device not in range for too many times. This is a firmware problem and has to do with bluetooth and wifi coexistence on the rpi0w. The solution i found is to replace the brcmfmac43430-sdio.bin with brcmfmac43436s-sdio.bin. Both are located in /lib/firmware/brcm on the rpi0w. Replacing it doesn't cause any additional problems, at least none that I am aware of, but it fixes the said issue. The 43436s firmware is for the newer, rpi0 2w, but is compatible with the 0w. Be sure to back up the original firmware in case of problems.
