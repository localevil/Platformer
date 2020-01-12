cmake_minimum_required(VERSION 2.8)
project(Platformer)

set(LIBS
    SDL2
	SDL2_image)

set(HDR
	headers/collision.h
	headers/renderer.h
	headers/player.h
	)

set(SRC
    src/main.c
	src/collision.c
	src/renderer.c
	src/player.c
	)

include_directories(headers)

add_compile_options( -g -fexceptions --std=c11 -Wall -O22)
add_executable(${PROJECT_NAME} ${SRC} ${HDR})

target_link_libraries(${PROJECT_NAME} ${LIBS})
