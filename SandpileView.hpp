#pragma once

#include "VertexGrid.hpp"
#include <windows.h>

class SandpileView
{
private:
    HWND hwnd = 0;
    RECT old_size = {};

    int timer_id = 1; // TODO: Pass per-instance?
    VertexGrid* vertex_grid = nullptr;
    VertexGrid* snake = nullptr;

    static const char* window_class_name;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

public:
    SandpileView(HINSTANCE hInstance);
    void show_window(int nCmdShow);
};
