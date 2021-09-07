#include "Scaffold.h"

#include <CppLog/Logger.h>

#include <Core/InputSystem/Input.h>
#include <Core/Window/WindowManager.h>
#include <Core/Utils/ArgProcessor.h>
#include <Core/Utils/StringUtils.h>
#include <Core/Ecs/SystemProto.h>
#include <Core/Dispatching/Dispatching.h>
#include <Core/Exceptions/BaseException.h>

#include <Renderer/Renderer.h>

USING_LOGGER


namespace scaffold
{
	void RunScaffold(int argc, char* argv[])
	{
		try
		{
			arg::AddSynonyms("--DebugLevel", { "--Debug" });
			arg::ProcessArgs(argc, argv);

			new cpplog::Logger("log.txt", "Main", arg::GetKwarg<int>("--DebugLevel", 0));

		window::StartSDL();
		window::mainWindow = window::StartWindow("Test Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
		window::GetInstance(window::mainWindow)->onClose.connect<&dispatch::StopCoreLoop>();

		input::AddDevice<input::InputDevice_Keyboard, std::string>("keyboard", "keyboard");
		input::AddDevice<input::InputDevice_Mouse, std::string>("mouse", "mouse");
		input::keyboard = input::GetDevice("keyboard");
		input::mouse = input::GetDevice("mouse");

			rendering::InitRenderer();


			dispatch::CoreLoop();


			ecs::SystemProto::Cleanup();

			input::ClearActions();
			input::ClearDevices();

			window::Shutdown();

			cpplog::Logger::Destruct();
		}
		catch (const exceptions::BaseException& e)
		{
			std::string msg = utils::string::ReplaceAll(e.Message(), "\n", "\n    ");
			Logger::Lock(Logger::ERROR) << "Unhandled " << e.ExceptionType() << " Exception at: " << e.File() << "[" << e.Line() << "]\n    "
				<< "Message: " << msg << Logger::endl;
		}
	}
}