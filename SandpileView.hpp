#pragma once

#include "VertexGrid.hpp"
#include "Snake.hpp"
#include "SnakeBoard.hpp"

#include <windows.h>

#include <vector>

class SandpileView
{
private:
    HWND hwnd = 0;
    RECT old_size = {};

    int timer_id = 1; // TODO: Pass per-instance?
    unsigned int timer_ms = 50;

    VertexGrid* vertex_grid = nullptr;
    SnakeBoard snakes;

    static const char* window_class_name;

    static LRESULT CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

    void DrawScene(HDC hdc, RECT const& rcClient);

public:
    explicit SandpileView(HINSTANCE hInstance);
    static void register_window_class(HINSTANCE hInstance);
    void show_window(int nCmdShow = SW_SHOWNORMAL);
    bool is_open() const;
    void set_foreground();
};
