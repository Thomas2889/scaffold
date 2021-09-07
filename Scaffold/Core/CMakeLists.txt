cmake_minimum_required (VERSION 3.18)

 add_library (
 	Core
	"Core/Dispatching/Dispatching.cpp"
	
	"Core/Ecs/EntityRegistry.cpp"
	"Core/Ecs/SystemProto.cpp"
	
	"Core/InputSystem/Input.cpp"
	"Core/InputSystem/InputAction.cpp"
	"Core/InputSystem/InputDevice.cpp"
	"Core/InputSystem/InputDrivers.cpp"
	
	"Core/Window/Window.cpp"
	"Core/Window/WindowManager.cpp"

	"Core/Utils/StringUtils.cpp"
	"Core/Utils/ArgProcessor.cpp"
	"Core/Utils/Math.cpp"
	"Core/Debugging/CPUProfiler.cpp")

set_target_properties(Core PROPERTIES PREFIX "scaffold-")

	
target_include_directories (Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Core")
target_include_directories (Core PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/#in/Include")
target_include_directories (Core PRIVATE "${CMAKE_SOURCE_DIR}/#in/Include")

target_link_libraries(Core
	PUBLIC "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/CppLog.lib"
	PUBLIC "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2.lib"
	PUBLIC "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2main.lib"
	PUBLIC "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2test.lib"
	)


if(${CMAKE_OS_NAME} STREQUAL "Windows")
	execute_process(COMMAND
		cmd /c call "${CMAKE_CURRENT_SOURCE_DIR}/#buildsteps/CopyHeaders.bat"
			"${CMAKE_CURRENT_SOURCE_DIR}/Core"
			"${CMAKE_BINARY_DIR}/#Headers/Core"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"

		RESULT_VARIABLE result
		OUTPUT_VARIABLE out
		ERROR_VARIABLE err
	)
endif()
