cmake_minimum_required(VERSION 3.20)
project(coro_toy)

set(CMAKE_CXX_STANDARD 20)

add_executable(coro_toy main.cpp SandpileView.cpp SandpileView.hpp VertexGrid.cpp VertexGrid.hpp SandpileData.cpp SandpileData.hpp Perlin.cpp Perlin.hpp Bezier.cpp Bezier.hpp Vector2.cpp Vector2.hpp Texture.cpp Texture.hpp Color.cpp Color.hpp WindowsErrorException.cpp WindowsErrorException.hpp Snake.cpp Snake.hpp GraphPaper.cpp GraphPaper.hpp SnakeBoard.cpp SnakeBoard.hpp LauncherWindow.cpp LauncherWindow.hpp
        resource.rc resource.h)

target_compile_options(coro_toy
        PRIVATE
        -mwindows
        )

target_link_libraries(coro_toy
        comctl32
        msimg32
        #gdi32
        )
