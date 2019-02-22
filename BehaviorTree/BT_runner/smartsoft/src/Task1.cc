//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#include "Task1.hh"
#include "BT_runner.hh"
#include "../../OCamlWrap/wrap.h"
#include "caml/callback.h"

#include <iostream>

#ifdef USE_BTCPP
#include <behaviortree_cpp/blackboard/blackboard_local.h>

using namespace BT;
using namespace tinyxml2;
#endif

using namespace std;

Task1::Task1(SmartACE::SmartComponent *comp) 
:	Task1Core(comp)
{
	std::cout << "constructor Task1\n";
}
Task1::~Task1() 
{
	std::cout << "destructor Task1\n";
}

#ifdef USE_BTCPP
// Create a dummy action for monitor BT
NodeStatus DummyAction(TreeNode& self)
{
//    sleep(1);
    return NodeStatus::SUCCESS;
}
#endif

int Task1::on_entry()
{
	// do initialization procedures here, which are called once, each time the task is started
	// it is possible to return != 0 (e.g. when initialization fails) then the task is not executed further

	char *dummy[] = {nullptr};
	std::cout << "Calling caml_startup" << std::endl;
	caml_startup(dummy);

//	std::string bt_filename(COMP->getGlobalState().getSettings().getBt_description() );
	std::string bt_filename("./bt_description.xml");
	std::string bt_skillList("skillList.xml");

	std::cout << "Reading BT from file " << bt_filename << std::endl;
	behaviourTree = read_bt(bt_filename.c_str());
	std::cout << "... done!" << std::endl;


#ifdef USE_BTCPP

	XMLDocument doc;
	tinyxml2::XMLError eResult = doc.LoadFile(bt_skillList.c_str());
	if (eResult != tinyxml2::XML_SUCCESS)
	{
		std::cout << "Cannot parse doc " << std::endl;
		return -1;
	}

	tinyxml2::XMLNode* root = doc.FirstChildElement("SkillList");
	if (root == nullptr)
	{
		std::cout << "SkillList not found " << std::endl;
		return -1;
	}

	std::cout << root->GetLineNum() << " " << root->ToText() << std::endl;

	for (auto child_element = root->FirstChildElement(); child_element;
		 child_element = child_element->NextSiblingElement())
	{
        std::cout << child_element->Name() << "." << child_element->Attribute("ID") << std::endl;
        if(string(child_element->Name()) == string("Action"))
			COMP->factory.registerSimpleAction(child_element->Attribute("ID"), DummyAction);
        if(string(child_element->Name()) == string("Condition"))
        	COMP->factory.registerSimpleCondition(child_element->Attribute("ID"), DummyAction);
	}
	std::cout << "buildTreeFromFile " << bt_filename << std::endl;

	// Important: when the object tree goes out of scope, all the TreeNodes are destroyed
	COMP->tree_cpp = buildTreeFromFile(COMP->factory, bt_filename,  Blackboard::create<BlackboardLocal>());

    std::cout << "///////////////////////// done " << std::endl;


    // Create some loggers
    logger_cout = make_shared<StdCoutLogger>(COMP->tree_cpp.root_node);
    logger_minitrace = make_shared<MinitraceLogger>(COMP->tree_cpp.root_node, "bt_trace.json");
    logger_file = make_shared<FileLogger>(COMP->tree_cpp.root_node, "bt_trace.fbl");
    publisher_zmq = make_shared<PublisherZMQ>(COMP->tree_cpp.root_node);

    printTreeRecursively(COMP->tree_cpp.root_node);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    for(auto node : COMP->tree_cpp.nodes)
        COMP->nodeMap[node->name()] = node;

// For debug only
/*
	for(int i : {1,2,3,0})
	{
		NodeStatus status = NodeStatus(i);
		// Keep on ticking until you get either a SUCCESS or FAILURE state
		for(auto node : COMP->tree_cpp.nodes)
		{
			node->setStatus((NodeStatus)i);
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
	}
	COMP->nodeMap["BottleGrasped"]->setStatus(NodeStatus::SUCCESS);
*/
#endif


	return 0;
}

int Task1::on_execute()
{
	// this method is called from an outside loop,
	// hence, NEVER use an infinite loop (like "while(1)") here inside!!!
	// also do not use blocking calls which do not result from smartsoft kernel
	
	// to get the incoming data, use this methods:
	Smart::StatusCode status;

	std::cout << "\n\n-------------------------\n" << "on_execute() " << std::endl;

	int ret = tick(behaviourTree);
	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	std::cout << "-> tick return value is " << ret << std::endl;

	int secs = 1;
	std::cout << "sleeping " << secs << " sec " << std::endl;
	usleep(100 * 1000);

	// it is possible to return != 0 (e.g. when the task detects errors), then the outer loop breaks and the task stops
	return 0;
}

int Task1::on_exit()
{
	// use this method to clean-up resources which are initialized in on_entry() and needs to be freed before the on_execute() can be called again
	return 0;
}
