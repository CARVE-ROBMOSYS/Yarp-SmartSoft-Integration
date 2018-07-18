# Yarp-SmartSoft-Integration
SW components used to integrate YARP modules in SmartSoft

## Dependencies
- [YARP](https://github.com/robotology/yarp)
	- Installation:
	```bash
	$ git clone https://github.com/robotology/yarp.git
	$ cd yarp && mkdir build && cd build
	$ make
	$ make install (optional)
	```
- [AceSmartSoft](https://github.com/Servicerobotics-Ulm/AceSmartSoftFramework.git)
	- Installation:
		```bash
	$ git clonehttps://github.com/Servicerobotics-Ulm/AceSmartSoftFramework.git
	$ cd AceSmartSoftFramework && mkdir build && cd build
	$ make
	$ make install (optional)
	```

:warning: If you are not an installer guy remember to export   `YARP_DIR` and `AceSmartSoft_DIR`
pointing to the build directory of `yarp` and `AceSmartSoft` respectively.
