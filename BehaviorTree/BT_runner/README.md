<!--- This file is generated from the BT_runner.componentDocumentation model --->
<!--- do not modify this file manually as it will by automatically overwritten by the code generator, modify the model instead and re-generate this file --->

# BT_runner Component

![BT_runner-ComponentImage](https://github.com/Servicerobotics-Ulm/ComponentRepository/blob/master/BT_runner/model/BT_runnerComponentDefinition.jpg)


| Metaelement | Documentation |
|-------------|---------------|
| License |  |
| Hardware Requirements |  |
| Purpose |  |



This component load a Behavior tree from xml file and run it.

Optionally, it can show real-time status of BT by using Groot GUI (https://github.com/BehaviorTree/Groot).

To enable it, download and compile BehaviorTree.cpp (https://github.com/BehaviorTree/BehaviorTree.CPP), then set environment variables
BehaviorTree_DIR pointing to the build folder
extend LD_LIBRARY_PATH with BehaviorTree_DIR/bin (or to the folder containing libbehaviortree_cpp.so if you installed the library)

If the library is found, the GUI support will be compiled automatically
