#pragma once

#include <windows.h>


class LauncherWindow
{
private:
    HINSTANCE hInstance;

    static const char* window_class_name;

    static INT_PTR CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    INT_PTR WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit LauncherWindow(HINSTANCE hInstance);
    int show_dialog();
};
