#pragma once

#include "SandpileView.hpp"

#include <windows.h>

#include <memory>

class LauncherWindow
{
private:
    HINSTANCE hInstance;
    std::unique_ptr<SandpileView> snakes_demo;

    static const char* window_class_name;

    static INT_PTR CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    INT_PTR WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit LauncherWindow(HINSTANCE hInstance);
    int show_dialog();
};
