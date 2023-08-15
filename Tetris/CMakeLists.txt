cmake_minimum_required(VERSION 3.5)
project(Tetris)

set(SOURCES
    src/tetris.cpp
    src/check.cpp
)

add_executable(Tetris ${SOURCES})

file(COPY images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(Tetris
    sfml-graphics
    sfml-window
    sfml-system
)

