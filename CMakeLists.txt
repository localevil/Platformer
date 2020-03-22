cmake_minimum_required(VERSION 3.5)
project(Platformer LANGUAGES C)

set(LIBS
	SDL2
	SDL2_image
	m
	)

set(HDR
	"headers/collision.h"
	"headers/renderer.h"
	"headers/player.h"
	"headers/engine.h"
	"headers/tilemap.h"
	"headers/vector2d.h"
	)

set(SRC
	"sources/main.c"
	"sources/engine.c"
	"sources/collision.c"
	"sources/renderer.c"
	"sources/player.c"
	"sources/tilemap.c"
	"sources/vector2d.c"
	)

#include_directories(sources)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_compile_options(-fexceptions --std=c11 -Wall) #-O2
add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_include_directories(${PROJECT_NAME} PUBLIC headers)
target_link_libraries(${PROJECT_NAME} ${LIBS})
