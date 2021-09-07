cmake_minimum_required (VERSION 3.18)

 add_library (
 	Scaffold
	 "src/Scaffold.cpp")

	
target_include_directories (Scaffold PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories (Scaffold PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/#in/Include")
target_include_directories (Scaffold PRIVATE "${CMAKE_SOURCE_DIR}/#in/Include")

target_link_libraries(Scaffold
	)

	
target_link_libraries (Scaffold PUBLIC Core)
target_include_directories (Scaffold PUBLIC "${CMAKE_SOURCE_DIR}/Core")
target_link_libraries (Scaffold PUBLIC Renderer)
target_include_directories (Scaffold PUBLIC "${CMAKE_SOURCE_DIR}/Renderer")


if(${CMAKE_OS_NAME} STREQUAL "Windows")
	execute_process(COMMAND
		cmd /c call "${CMAKE_CURRENT_SOURCE_DIR}/#buildsteps/CopyHeaders.bat"
			"${CMAKE_CURRENT_SOURCE_DIR}/src"
			"${CMAKE_BINARY_DIR}/#Headers"
		WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"

		RESULT_VARIABLE result
		OUTPUT_VARIABLE out
		ERROR_VARIABLE err
	)
endif()
