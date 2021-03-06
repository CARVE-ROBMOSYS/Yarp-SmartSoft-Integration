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
#include "CompHandler.hh"
#include "SequencePath.hh"

#include <iostream>

// include communication objects

#include <list>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void CompHandler::onStartup() 
{
	std::cout << "startup - put your startupCode in CompHandler::onStartup()!!!\n";
		Smart::StatusCode status;

		/* Load config file */
//		std::string file(COMP->getGlobalState().getSettings().getConfigFile());
		std::string file = "config.ini";

	    std::ifstream myFile;

	    myFile.open(file.c_str() , std::ios::in);
	    if(!myFile.is_open())
	    {
			std::string errorStr = "\nerror opening file " + file;
			throw std::invalid_argument(errorStr);
	    }
	    else
	    {
			/* Read it */
			string line;
			std::cout << "\n reading file " << file << std::endl;

			bool check_version = false;
			while(!myFile.eof())
			{
				getline(myFile, line);

	//			std::cout << "Got a new line:  " << line << std::endl;

				istringstream ticker(line);
				vector<string> tokens {istream_iterator<string>{ticker}, istream_iterator<string>{}};
	//			std::cout << "tokens size: " << tokens.size() << std::endl;

				if(!check_version)
				{
					if(tokens[0] != "version")
					{
						std::string errorStr = "\nInput file " + file + " missing 'version' field";
						throw std::invalid_argument(errorStr);
					}

					if(tokens[1] != "1")
					{
						std::string errorStr = "\nInput file " + file + " missing 'version' not supported. Only supported version is 1";
						throw std::invalid_argument(errorStr);
					}
					check_version = true;
					std::cout << "Version check ok -- file version is " << tokens[1] << std::endl;
					continue;
				}

				if(tokens.size() == 0)		// skip blank lines
					continue;
	/*
				for(int i=0;  i< tokens.size(); i++)
					std::cout << "token number " << i << " is " << tokens[i] << std::endl;
	*/
				COMP->inputData.push_back(tokens[0]);
			}
			myFile.close();
			std::cout << "Config file loaded\n";
	    }

	    // Instantiate devices

	    if(COMP->inputData.size() < 2)
	    {
			std::string errorStr = "\nInput file " + file + " is empty";
			throw std::invalid_argument(errorStr);
	    }

	    // echo back the input data
	    for (auto tokens : COMP->inputData)
	    {
	    	std::cout << tokens << "\n";
	    }

		// Start all services. If you need manual control, use the content of this function to
		// connect and start each service individually, e.g:
		// COMP->connectMyPortName("SmartExampleComponent", "examplePort");
		status = COMP->connectAndStartAllServices();

		// Start all tasks. If you need manual control, use the content of this function to
		// start each task individually.
		COMP->startAllTasks();

		// Start all timers. If you need manual control, use the content of this function to
		// start each timer individually.
		COMP->startAllTimers();

		// Notify the component that setup/initialization is finished.
		// You may move this function to any other place.
		COMP->setStartupFinished();
}

void CompHandler::onShutdown() 
{
	std::cout << "shutdown - put your cleanup code in CompHandler::onShutdown()!!!\n";
	
}
