#Specify a minimum version for CMake
cmake_minimum_required(VERSION 2.8)

#Project name
project(citadel)

#Set the output folder
set(CITADEL_ROOT_DIR ${CMAKE_SOURCE_DIR}/../../)
set(CITADEL_DIST_DIR ${CITADEL_ROOT_DIR}dist/)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CITADEL_DIST_DIR}lib/linux)

set(CMAKE_CXX_STANDARD 14)

include_directories(../../)

add_library(
	citadel
	STATIC

	../../castle/app/Activity.linux.cpp
	../../castle/game/Game.cpp

	../../keep/window/OpenGLWindow.linux.cpp
	
	../../watchtower/device/OpenGL/OpenGLDevice.linux.cpp
)

find_library( X11 x11 )
find_library( GL gl )
find_library( GLU glu )

target_link_libraries(
	citadel

	x11
	gl
	glu
)

add_custom_command(
	TARGET citadel POST_BUILD
	COMMAND rsync
	ARGS -am --include="*.h" --exclude="dist" --include="*/" --exclude="*" ${CITADEL_ROOT_DIR} ${CITADEL_DIST_DIR}
	COMMENT "Copying header files."
)
