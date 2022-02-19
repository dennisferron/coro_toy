#pragma once

#include "SnakesDemo.hpp"
#include "AdventureWindow.hpp"

#include <windows.h>

#include <memory>

class LauncherWindow
{
private:
    HINSTANCE hInstance;
    std::shared_ptr<SnakesDemo> snakes_demo;
    std::shared_ptr<AdventureWindow> adventure_window;

    static INT_PTR CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    INT_PTR WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit LauncherWindow(HINSTANCE hInstance);
    int show_dialog();
};
