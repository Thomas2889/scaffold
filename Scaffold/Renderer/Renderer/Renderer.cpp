#include "Renderer.h"

#include <GL/glew.h>
#include <CppLog/Logger.h>

#include <Core/Window/WindowManager.h>
#include <Core/Ecs/SystemProto.h>
#include <Core/Exceptions/GenericExceptions.h>

#include "Exceptions/RenderingExceptions.h"

USING_LOGGER;


namespace scaffold::rendering
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


		class RendererSystem : public ecs::SystemProto
		{
			DEFINE_SYSTEM_PROTO(RendererSystem);

			GLuint VAO;
			GLuint VBO;
			GLuint shaderProgram;

			System_Start()
			{
				float vertices[] = {
					-0.5f, -0.5f, 0.0f,
					 0.5f, -0.5f, 0.0f,
					 0.0f,  0.5f, 0.0f
				};

				glGenVertexArrays(1, &VAO);
				glBindVertexArray(VAO);

				glGenBuffers(1, &VBO);
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				const char* vertexShaderSource = "#version 330 core\n"
					"layout (location = 0) in vec3 aPos;\n"
					"void main()\n"
					"{\n"
					"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
					"}\0";

				const char* fragmentShaderSource = "#version 330 core\n"
					"out vec4 FragColor;\n"
					"void main()\n"
					"{\n"
					"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
					"}\0";

				GLuint vertexShader;
				vertexShader = glCreateShader(GL_VERTEX_SHADER);
				glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
				glCompileShader(vertexShader);

				GLuint fragmentShader;
				fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
				glCompileShader(fragmentShader);

				shaderProgram = glCreateProgram();
				glAttachShader(shaderProgram, vertexShader);
				glAttachShader(shaderProgram, fragmentShader);
				glLinkProgram(shaderProgram);

				glUseProgram(shaderProgram);
				glDeleteShader(vertexShader);
				glDeleteShader(fragmentShader);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
				glEnableVertexAttribArray(0);
			}

			System_Render()
			{
				glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				glUseProgram(shaderProgram);
				glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);

				SDL_GL_SwapWindow(window::GetInstance(window::mainWindow)->getWindow());
			}
		};
	}
	IMPLEMENT_SYSTEM_PROTO_PRI(RendererSystem, -100);

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
