#pragma once

#include "VertexGrid.hpp"
#include "Snake.hpp"

#include <windows.h>

class SandpileView
{
private:
    HWND hwnd = 0;
    RECT old_size = {};

    int timer_id = 1; // TODO: Pass per-instance?
    unsigned int timer_ms = 50;

    VertexGrid* vertex_grid = nullptr;
    Snake* snake = nullptr;

    static const char* window_class_name;

    static LRESULT CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

    void DrawScene(HDC hdc, RECT const& rcClient);

public:
    SandpileView(HINSTANCE hInstance);
    void show_window(int nCmdShow);
};
