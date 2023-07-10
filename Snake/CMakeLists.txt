cmake_minimum_required(VERSION 3.5)
project(Tetris)

set(SOURCES
    Snake.cpp
    Tick.cpp
)

add_executable(Snake ${SOURCES})

file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Snake
    sfml-graphics
    sfml-window
    sfml-system
)

