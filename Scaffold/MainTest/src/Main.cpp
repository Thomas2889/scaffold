#include "InputSystem/Input.h"

#include <thread>


bool running = true;

void TestInput(scaffold::input::InputAction* action)
{
	if (action->GetData<bool>() == true)
		cpplog::Logger::Log("Did input!", cpplog::Logger::DEBUG);
}

#undef main
void main()
{
	new cpplog::Logger("log.txt", "Main", 4);

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	SDL_Window* window = SDL_CreateWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 450, SDL_WINDOW_RESIZABLE);

	scaffold::input::AddDevice<scaffold::input::InputDevice_Keyboard, std::string>("keyboard", "keyboard");
	scaffold::input::AddDevice<scaffold::input::InputDevice_Mouse, std::string>("mouse", "mouse");

	scaffold::input::CreateAction("TestInput", "keyboard/W").onValueChange.connect<&TestInput>();

	while (running)
	{
		SDL_PumpEvents();

		scaffold::input::intern::InputEntry::PreUpdate();

		SDL_Event e;
		int currentEvents = 0;
		const int maxEvents = 50;
		while (SDL_PollEvent(&e) && currentEvents < maxEvents) // poll events
		{
			currentEvents++;

			if (e.type == SDL_WINDOWEVENT)
			{
				switch (e.window.event)
				{
				case SDL_WINDOWEVENT_CLOSE:
					running = false;
					break;
				}
			}
			else
			{
				switch (e.type)
				{
				case SDL_KEYUP:
				case SDL_KEYDOWN:
				case SDL_MOUSEMOTION:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEWHEEL:
					scaffold::input::intern::InputEntry::ProcessEvent(e);
					break;
				}
			}
		}

		scaffold::input::intern::InputEntry::PostUpdate();


		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	cpplog::Logger::Destruct();
}