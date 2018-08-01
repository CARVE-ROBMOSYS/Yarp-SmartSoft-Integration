Yarp-SmartSoft-Integration
==========================

SW components used to integrate YARP modules in SmartSoft

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
  $ cmake ..
  $ make -j
  $ make install (optional)
```
It is possible to compile the examples running `cmake -DCOMPILE_examples=ON ..`

# Usage

- `libYARP_smartsoft`: to include it in your project add this line in your `CMakeLists.txt`

```cmake
find_package(YARP COMPONENTS smartsoft)
```

# Documentation

If doxygen is installed, `make dox` will generate the documentation in the build
directory.

