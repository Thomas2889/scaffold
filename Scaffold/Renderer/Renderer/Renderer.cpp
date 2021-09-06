#include "Renderer.h"

#include <GL/glew.h>
#include <CppLog/Logger.h>

#include "Core/Window/WindowManager.h"

#include "Exceptions/RenderingExceptions.h"

USING_LOGGER;


namespace scaffold::renderer
{
	namespace
	{
		SDL_GLContext glContext;

		void GLAPIENTRY OpenGLDebugCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
		{
			std::string msg;
			msg = std::string("[") + std::to_string(id) + std::string("] ") + std::string(message);

			switch (severity)
			{
			case GL_DEBUG_SEVERITY_HIGH:
				Logger::Log(msg, 100);
				break;
			case GL_DEBUG_SEVERITY_MEDIUM:
			case GL_DEBUG_SEVERITY_LOW:
				Logger::Log(msg, 101);
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION:
				Logger::Log(msg, 102);
				break;
			}
		}
	}

	void InitRenderer()
	{
		glContext = SDL_GL_CreateContext(window::GetInstance(window::mainWindow)->getWindow());

		if (glewInit() != GLEW_OK)
			throw exceptions::GlException(std::string("GlewInit has failed."), glGetError(), __FILE__, __LINE__);

		Logger::RegisterNewTag(100, "GlError", 1, Logger::COLOR_BRIGHT_RED, Logger::COLOR_BLACK, "renderlog.txt");
		Logger::RegisterNewTag(101, "GlWarning", 3, Logger::COLOR_BRIGHT_YELLOW, Logger::COLOR_BLACK, "renderlog.txt");
		Logger::RegisterNewTag(102, "GlInfo", 5, Logger::COLOR_WHITE, Logger::COLOR_BLACK, "renderlog.txt");

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(OpenGLDebugCallback, nullptr);

		glViewport(0, 0, window::GetInstance(window::mainWindow)->getWidth(), window::GetInstance(window::mainWindow)->getHeight());
		window::GetInstance(window::mainWindow)->AddWindowCallback([](SDL_Event e, void* _data) {
			glViewport(0, 0, window::GetInstance(window::mainWindow)->getWidth(), window::GetInstance(window::mainWindow)->getHeight());
			});


	}
}
