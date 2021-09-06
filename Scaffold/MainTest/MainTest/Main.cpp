#include "Core/Scaffold.h"
#include "Core/Ecs/SystemProto.h"

#include <thread>

#include <CppLog/Logger.h>

USING_LOGGER;


#define TestSystemMacro(__name__, __pri__)	class __name__ : public scaffold::ecs::SystemProto \
										{ \
											DEFINE_SYSTEM_PROTO(__name__); \
										public: \
											System_Start() \
											{ \
												Logger::Lock() << #__name__ << Logger::endl; \
											} \
										}; \
										IMPLEMENT_SYSTEM_PROTO_PRI(__name__, __pri__); \

TestSystemMacro(Test1, 1);
TestSystemMacro(Test2, 2);
TestSystemMacro(Test3, 3);
TestSystemMacro(Test4, 4);
TestSystemMacro(Test5, 5);
TestSystemMacro(Test6, 6);
TestSystemMacro(Test7, 7);
TestSystemMacro(Test8, 8);
TestSystemMacro(Test9, 9);
TestSystemMacro(Test10, 10);
TestSystemMacro(Test11, 11);
TestSystemMacro(Test12, 12);
TestSystemMacro(Test13, 13);
TestSystemMacro(Test14, 14);

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