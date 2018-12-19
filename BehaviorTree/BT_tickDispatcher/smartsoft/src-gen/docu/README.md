<!--- This file is generated from the BT_tickDispatcher.componentDocumentation model --->
<!--- do not modify this file manually as it will by automatically overwritten by the code generator, modify the model instead and re-generate this file --->

# BT_tickDispatcher Component

![BT_tickDispatcher-ComponentImage](https://github.com/Servicerobotics-Ulm/ComponentRepository/blob/master/BT_tickDispatcher/model/BT_tickDispatcherComponentDefinition.jpg)


| Metaelement | Documentation |
|-------------|---------------|
| License |  |
| Hardware Requirements |  |
| Purpose |  |



## Service Ports


## Component Parameters BT_tickDispatcherParams

### InternalParameter Settings

| Attribute Name | Attribute Type | Description |
|----------------|----------------|-------------|
| tickManager_localPort | String |  |
| configFile | String |  |

### ParameterSetInstance ConfigParams

#### TriggerInstance configFile

active = false

Drop the current map and create a new map with free cells of dimensions [mm] ?xsize and ?ysize. The map is initialized with an offset [mm] ?xoff and ?yoff relative to world coordinates. The cellsize used for this map as well as the obstacle growing type are specified in the ini-configuration. The id ?id will be assigned to the map to synchronize components, for example with SmartPlannerBreadthFirstSearch and SmartCdlServer.
Using this parameter is only allowed in neutral state.

