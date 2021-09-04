cmake_minimum_required (VERSION 3.18)

 add_library (
 	Core
	"src/Dispatching/Dispatching.cpp"
	
	"src/Ecs/EntityRegistry.cpp"
	"src/Ecs/SystemProto.cpp"
	
	"src/InputSystem/Input.cpp"
	"src/InputSystem/InputAction.cpp"
	"src/InputSystem/InputDevice.cpp"
	"src/InputSystem/InputDrivers.cpp"
	
	"src/Window/Window.cpp"
	"src/Window/WindowManager.cpp"

	"src/Utils/StringUtils.cpp"
	"src/Utils/ArgProcessor.cpp"
	"src/Utils/Math.cpp"
	"src/Debugging/CPUProfiler.cpp"
	
	"src/Scaffold.cpp")

	
target_include_directories (Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories (Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/#in/Include")
target_include_directories (Core PRIVATE "${CMAKE_SOURCE_DIR}/#in/Include")

target_link_libraries(Core
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/CppLog.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2main.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2test.lib"
	)


if(${CMAKE_OS_NAME} STREQUAL "Windows")
	execute_process(COMMAND
		cmd /c call "${CMAKE_CURRENT_SOURCE_DIR}/#buildsteps/CopyHeaders.bat"
			"${CMAKE_CURRENT_SOURCE_DIR}/src"
			"${CMAKE_BINARY_DIR}/#Headers/Core"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"

		RESULT_VARIABLE result
		OUTPUT_VARIABLE out
		ERROR_VARIABLE err
	)
endif()
