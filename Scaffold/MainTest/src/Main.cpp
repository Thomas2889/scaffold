#include "Core/Scaffold.h"
#include "Core/Ecs/SystemProto.h"

#include <thread>


class TestSystem : public scaffold::ecs::SystemProto
{
	DEFINE_SYSTEM_PROTO(TestSystem);
		
public:

};
IMPLEMENT_SYSTEM_PROTO(TestSystem);


#undef main
void main(int argc, char* argv[])
{
	scaffold::RunScaffold(argc, argv);
}