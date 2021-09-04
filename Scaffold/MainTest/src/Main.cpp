#include "Core/InputSystem/Input.h"
#include "Core/Window/WindowManager.h"
#include "Core/Utils/ArgProcessor.h"
#include "Core/Ecs/SystemProto.h"
#include "Core/Dispatching/Dispatching.h"
#include "Core/Debugging/CPUProfiler.h"

#include <thread>


using namespace scaffold;


class TestSystem : public ecs::SystemProto
{
	DEFINE_SYSTEM_PROTO(TestSystem);
		
public:

};
IMPLEMENT_SYSTEM_PROTO(TestSystem);


#undef main
void main(int argc, char* argv[])
{
	arg::AddSynonyms("--DebugLevel", { "--Debug" });
	arg::ProcessArgs(argc, argv);

	new cpplog::Logger("log.txt", "Main", arg::GetKwarg<int>("--DebugLevel", 0));

	window::StartSDL();
	window::mainWindow = window::StartWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &dispatch::StopCoreLoop);

	input::AddDevice<input::InputDevice_Keyboard, std::string>("keyboard", "keyboard");
	input::AddDevice<input::InputDevice_Mouse, std::string>("mouse", "mouse");


	dispatch::CoreLoop();


	ecs::SystemProto::Cleanup();

	input::ClearActions();
	input::ClearDevices();

	window::Shutdown();

	cpplog::Logger::Destruct();
}