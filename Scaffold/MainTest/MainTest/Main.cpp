#include <Scaffold.h>
#include <Core/Ecs/SystemProto.h>
#include <Core/InputSystem/Input.h>

#include <thread>

#include <CppLog/Logger.h>

USING_LOGGER;


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