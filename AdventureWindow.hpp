#pragma once

#include "SnakesDemo.hpp"

#include <windows.h>

#include <memory>

class AdventureWindow
{
private:
    HINSTANCE hInstance;
    std::unique_ptr<SnakesDemo> snakes_demo;

    static INT_PTR CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    INT_PTR WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit AdventureWindow(HINSTANCE hInstance);
    int show_dialog();
};
