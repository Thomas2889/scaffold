cmake_minimum_required (VERSION 3.18)

 add_library (
 	InputSystem
	"src/Input.cpp"
	"src/InputAction.cpp"
	"src/InputDevice.cpp"
	"src/InputDrivers.cpp"
)


target_include_directories (InputSystem PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/#in/Include")
target_include_directories (InputSystem PRIVATE "${CMAKE_SOURCE_DIR}/#in/Include")
target_include_directories (MainTest PRIVATE "${CMAKE_BINARY_DIR}/#Headers")

target_link_libraries(InputSystem
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/CppLog.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/glew32.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2main.lib"
	PRIVATE "${CMAKE_SOURCE_DIR}/#in/Lib/${CMAKE_OS_NAME}/${CMAKE_PLATFORM_NAME}-${CMAKE_BUILD_TYPE}/SDL2test.lib"
	)


if(${CMAKE_OS_NAME} STREQUAL "Windows")
	execute_process(COMMAND
		cmd /c call "${CMAKE_CURRENT_SOURCE_DIR}/#buildsteps/CopyHeaders.bat"
			"${CMAKE_CURRENT_SOURCE_DIR}/src"
			"${CMAKE_BINARY_DIR}/#Headers/InputSystem"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"

		RESULT_VARIABLE result
		OUTPUT_VARIABLE out
		ERROR_VARIABLE err
	)
endif()
