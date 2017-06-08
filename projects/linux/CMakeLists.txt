#Specify a minimum version for CMake
cmake_minimum_required(VERSION 2.8)

#Project name
project(citadel)

#Set the output folder
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 14)

include_directories(../../)

add_library(
	citadel
	STATIC

	../../castle/app/Activity.pc.cpp
	../../castle/game/Game.cpp

  ../../keep/window/Window.xlib.cpp
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
