#include "Core/Scaffold.h"
#include "Core/Ecs/SystemProto.h"

#include <thread>

#include <CppLog/Logger.h>

USING_LOGGER;


#define TestSystemMacro(__name__, __pri__)	class __name__ : public scaffold::ecs::SystemProto \
											{ \
												DEFINE_SYSTEM_PROTO(__name__); \
												System_Start() { Logger::Lock() << #__name__ << Logger::endl; } \
											}; \
											IMPLEMENT_SYSTEM_PROTO_PRI(__name__, __pri__);


class TestSystem : public scaffold::ecs::SystemProto
{
	DEFINE_SYSTEM_PROTO(TestSystem);
};
IMPLEMENT_SYSTEM_PROTO(TestSystem);


#undef main
void main(int argc, char* argv[])
{
	scaffold::RunScaffold(argc, argv);
}