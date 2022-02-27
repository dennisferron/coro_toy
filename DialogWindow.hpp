#pragma once

#include "Window.hpp"

class DialogWindow : public Window
{
protected:

    static INT_PTR CALLBACK DlgProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam);

public:
    explicit DialogWindow(HINSTANCE hInstance);
};


