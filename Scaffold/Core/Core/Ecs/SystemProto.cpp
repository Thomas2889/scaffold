#include "SystemProto.h"


namespace scaffold::ecs
{
	SystemProto* SystemProto::instance;

	std::unordered_map<std::string, SystemProto*>* SystemProto::systemMap;
	std::vector<SystemProto*>* SystemProto::systemList;

	SystemProto::SystemProto(std::string uid, int priority) : systemUID(uid), priority(priority)
	{
		instance = this;
	}
}
