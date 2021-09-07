#include "Window.h"


namespace scaffold::window
{
	Window::Window(
		std::string _windowTitle,
		uint32_t _windowXPos,
		uint32_t _windowYPos,
		uint32_t _windowWidth,
		uint32_t _windowHeight,
		uint32_t _windowFlags
	) : onEvent(signalEvent), onClose(signalClose), onResize(signalResize)
	{
		title = _windowTitle;
		width = _windowWidth;
		height = _windowHeight;
		sdlWindow = SDL_CreateWindow(title.data(), _windowXPos, _windowYPos, width, height, _windowFlags);
	}

	Window::~Window()
	{
		SDL_DestroyWindow(sdlWindow);
	}
}
