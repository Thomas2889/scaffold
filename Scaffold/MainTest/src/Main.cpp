#include "Core/Scaffold.h"
#include "Core/Ecs/SystemProto.h"

#include <CppLog/Logger.h>
#include <vulkan/vulkan.hpp>


USING_LOGGER;


class TestSystem : public scaffold::ecs::SystemProto
{
	DEFINE_SYSTEM_PROTO(TestSystem);
		
public:
	System_Start()
	{

	}
};
IMPLEMENT_SYSTEM_PROTO(TestSystem);


#undef main
void main(int argc, char* argv[])
{
	scaffold::RunScaffold(argc, argv);
}