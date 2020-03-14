cmake_minimum_required(VERSION 3.5)
project(Platformer LANGUAGES C)

set(LIBS
    SDL2
    SDL2_image)

set(HDR
    "headers/collision.h"
    "headers/renderer.h"
    "headers/player.h"
    "headers/movement.h"
    )

set(SRC
    "sources/main.c"
    "sources/collision.c"
    "sources/renderer.c"
    "sources/player.c"
    "sources/movement.c"
	)

#include_directories(sources)

#file(COPY characters.png ${CMAKE_BINARY_DIR})

add_compile_options(-fexceptions --std=c11 -Wall) #-O2
add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_include_directories(${PROJECT_NAME} PUBLIC headers)
target_link_libraries(${PROJECT_NAME} ${LIBS})
