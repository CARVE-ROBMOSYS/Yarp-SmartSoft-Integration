Yarp-SmartSoft-Integration
==========================

SW components used to integrate YARP modules in SmartSoft

# Organization 
- Bridges: This folder contains SmartSoft components aimed to work as specialized bridges between pure YARP executable and pure SmartSoft components. They translate a message from a framework to the other one, by following proper communication patterns on each side. Furtthermore, this folder contains two components to run the behaviour trees inside SmartSoft and a communication message to propagate the Tick from it to the skills.

- Integration: This folder contains the software library based on YARP which reproduce the RobMoSys communication pattern and some examples.
  - libYARP_smartsoft: the library itself. It implements the communication patterns by wrapping YARP components and it mimic SmartSoft API. The library depends on YARP and includes `<aceSmartSoft.hh>`header for some enum definition.
  - examples: plain executable which instantiate a client / server device and run communication tests. There is an example for each pattern, both client and server. To compile the examples, the `COMPILE_examples` cmake flag has to be set in the main build folder.
  - SmartSoftComponentsExamples: SmartSoft component using the client/server from the integration library. There is a component for each pattern, both client and server. They can be imported into Eclipse MDSD toolchain and used as a standard component.


# Dependencies

`libYARP_smartsoft` needs a compiler that support c++14

- [YARP](https://github.com/robotology/yarp)
  - Installation on Linux:
```bash
    $ git clone https://github.com/robotology/yarp.git
    $ cd yarp && mkdir build && cd build
    $ make -j
    $ make install (optional)
```
- [AceSmartSoft](https://github.com/Servicerobotics-Ulm/AceSmartSoftFramework.git)
  - Installation on Linux:
```bash
    $ git clonehttps://github.com/Servicerobotics-Ulm/AceSmartSoftFramework.git
    $ cd AceSmartSoftFramework && mkdir build && cd build
    $ make -j
    $ make install (optional)
```

:warning: If you are not an installer guy remember to export `YARP_DIR` and
`AceSmartSoft_DIR` pointing to the build directory of `yarp` and `AceSmartSoft`
respectively.

# Installation on Linux

```bash
  $ git clone https://github.com/CARVE-ROBMOSYS/Yarp-SmartSoft-Integration
  $ cd Yarp-SmartSoft-Integration
  $ mkdir build && cd build
  $ SET CMAKE_INSTALL_PREFIX to $YARP_DIR
  $ cmake ..
  $ make -j
  $ make install
```
It is possible to compile the examples running `cmake -DCOMPILE_examples=ON ..`

:warning: It is suggested to install this repository, in this way the library
will be installed in the same build/install folder as YARP, so it can be easily find 
by CMake `FindPackage` directive.

# Usage

- `libYARP_smartsoft`: to include it in your project add this line in your `CMakeLists.txt`

```cmake
find_package(YARP COMPONENTS smartsoft)
```

# Documentation

If doxygen is installed, `make dox` will generate the documentation in the build
directory.

