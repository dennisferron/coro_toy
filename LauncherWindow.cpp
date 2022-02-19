#include "LauncherWindow.hpp"
#include "SnakesDemo.hpp"

#include "resource.h"

#include <stdexcept>
#include <vector>
#include <array>

LauncherWindow::LauncherWindow(HINSTANCE hInstance) :
    hInstance(hInstance)
{
}

int LauncherWindow::show_dialog()
{
    return DialogBoxParam(
        hInstance,
        MAKEINTRESOURCE(IDD_MAIN),
        NULL,
        LauncherWindow::WndProc_static,
        reinterpret_cast<LPARAM>(this)
    );
}

INT_PTR CALLBACK LauncherWindow::WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LauncherWindow* view_obj = nullptr;

    switch (msg)
    {
        case WM_INITDIALOG:
            view_obj = reinterpret_cast<LauncherWindow*>(lParam);
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(view_obj));
            break;
        default:
        {
            LONG_PTR user_data = GetWindowLongPtr(hwnd, GWLP_USERDATA);
            view_obj = reinterpret_cast<LauncherWindow*>(user_data);
        }
    }

    if (view_obj)
        return view_obj->WndProc(hwnd, msg, wParam, lParam);
    else
        return FALSE;
}


INT_PTR LauncherWindow::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_ADVENTURE:
                {
//                    if (adventure_window && adventure_window->is_open())
//                    {
//                        adventure_window->set_foreground();
//                    }
//                    else
//                    {
//                        snakes_demo.reset(new SnakesDemo(hInstance));
//                        snakes_demo->show_window();
//                    }
                    break;
                }
                case IDC_SNAKES:
                {
                    if (snakes_demo && snakes_demo->is_open())
                    {
                        snakes_demo->set_foreground();
                    }
                    else
                    {
                        snakes_demo = SnakesDemo::create(hInstance);
                        int x2 = snakes_demo.use_count();
                        snakes_demo->show_window();
                    }
                    break;
                }
                case IDC_TBD:
                    break;
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
