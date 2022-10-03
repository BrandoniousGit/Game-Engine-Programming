cmake_minimum_required(VERSION 3.0)
project(GEPENGINE)

include_directories(
	src
)

add_library(gepEngine
	src/gepEngine/core.cpp
	src/gepEngine/core.h
	src/gepEngine/gepEngine.h
)

add_executable(game
	src/game/main.cpp
	src/game/testScene.cpp
	src/game/testScene.h
)

target_link_libraries(game gepEngine)