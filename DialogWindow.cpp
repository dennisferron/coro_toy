#include "DialogWindow.hpp"

#include "resource.h"

#include <stdexcept>
#include <vector>
#include <array>

DialogWindow::DialogWindow(HINSTANCE hInstance) :
        Window(hInstance)
{
}

INT_PTR CALLBACK DialogWindow::DlgProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    INT_PTR result;

    if (msg == WM_INITDIALOG)
        Window::register_window(hwnd, reinterpret_cast<Window*>(lParam));

    if (auto found_window = Window::lookup_window(hwnd))
        result = std::dynamic_pointer_cast<DialogWindow>(
                found_window)->DlgProc(msg, wParam, lParam);
    else
        result = FALSE;

    if (msg == WM_NCDESTROY)
        Window::unregister_window(hwnd);

    return result;
}


INT_PTR DialogWindow::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;  // default: Message not handled.
}
