#include "confm.h"
#include "agent.h"

#define RINA_PREFIX "mad.conf"
#include <librina/logs.h>

namespace rinad{
namespace mad{

//Singleton instance
Singleton<ConfManager_> ConfManager;

//Public initialization/destruction API
void ConfManager_::init(const std::string& conf,
					const std::string& cl_logfile,
					const std::string& cl_loglevel){

	(void)conf;
	//TODO: read config and get logging level and file

	setLogLevel(cl_loglevel);
	setLogFile(cl_logfile);

	LOG_DBG("Initialized");
}

void ConfManager_::destroy(){

}

//Module configuration routine
void ConfManager_::configure(){


	//Configure the AP nameand instance ID
	//XXX get it from the configuration source (e.g. config file)
	std::string difName = "NMS-DIF";
	rina::ApplicationProcessNamingInformation info("mad_node1", "1");

	//Configure the MA
	ManagementAgent->setAPInfo(info);
	ManagementAgent->addNMSDIF(difName); //TODO read and do for all DIFs

	//TODO
}

//Singleton constructors and destructors
ConfManager_::ConfManager_(){
	//TODO
}

ConfManager_::~ConfManager_(){
	//TODO
}



}; //namespace mad
}; //namespace rinad


