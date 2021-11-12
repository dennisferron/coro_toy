cmake_minimum_required(VERSION 3.20)
project(coro_toy)

set(CMAKE_CXX_STANDARD 20)

add_executable(coro_toy main.cpp SandpileView.cpp SandpileView.hpp VertexGrid.cpp VertexGrid.hpp)

target_compile_options(coro_toy
        PRIVATE
        -mwindows
        )

target_link_libraries(coro_toy
        comctl32
        msimg32
        #gdi32
        )
