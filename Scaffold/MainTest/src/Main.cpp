#include "InputSystem/Input.h"
#include "Window/WindowManager.h"

#include <thread>


using namespace scaffold;


bool running = true;

void WindowShutdown()
{
	running = false;
}

#undef main
void main()
{
	new cpplog::Logger("log.txt", "Main", 4);

	window::StartSDL();
	window::mainWindow = window::StartWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN, &WindowShutdown);

	input::AddDevice<input::InputDevice_Keyboard, std::string>("keyboard", "keyboard");
	input::AddDevice<input::InputDevice_Mouse, std::string>("mouse", "mouse");


	while (running)
	{
		window::FlushEvents();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}


	input::ClearActions();
	input::ClearDevices();

	window::Shutdown();

	cpplog::Logger::Destruct();
}