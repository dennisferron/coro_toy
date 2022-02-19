#include "AdventureWindow.hpp"
#include "SnakesDemo.hpp"

#include "resource.h"

#include <stdexcept>
#include <vector>
#include <array>

AdventureWindow::AdventureWindow(HINSTANCE hInstance) :
        hInstance(hInstance)
{
}

int AdventureWindow::show_dialog()
{
    return DialogBoxParam(
            hInstance,
            MAKEINTRESOURCE(IDD_MAIN),
            NULL,
            AdventureWindow::WndProc_static,
            reinterpret_cast<LPARAM>(this)
    );
}

INT_PTR CALLBACK AdventureWindow::WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    AdventureWindow* view_obj = nullptr;

    switch (msg)
    {
        case WM_INITDIALOG:
            view_obj = reinterpret_cast<AdventureWindow*>(lParam);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(view_obj));
            break;
        default:
        {
            LONG_PTR user_data = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            view_obj = reinterpret_cast<AdventureWindow*>(user_data);
        }
    }

    if (view_obj)
        return view_obj->WndProc(hwnd, msg, wParam, lParam);
    else
        return FALSE;
}


INT_PTR AdventureWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                default:
                    break;
            }
            break;
        case WM_CLOSE:
            EndDialog(hwnd, 0);
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
