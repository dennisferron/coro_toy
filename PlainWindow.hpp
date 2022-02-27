#pragma once

#include "Window.hpp"

class PlainWindow : public Window
{
protected:
    PlainWindow(HINSTANCE hInstance);
    static LRESULT CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);
};


