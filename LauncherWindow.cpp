#include "LauncherWindow.hpp"
#include "SnakesDemo.hpp"

#include "resource.h"

#include <stdexcept>
#include <vector>
#include <array>

LauncherWindow::LauncherWindow(HINSTANCE hInstance) :
    DialogWindow(hInstance)
{
}

int LauncherWindow::create_dialog()
{
    return DialogBoxParam(
        hInstance,
        MAKEINTRESOURCE(IDD_MAIN),
        NULL,
        DialogWindow::DlgProc_static,
        reinterpret_cast<LPARAM>(this)
    );
}

INT_PTR LauncherWindow::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDC_ADVENTURE:
                {
                    if (adventure_window && adventure_window->is_open())
                    {
                        adventure_window->set_foreground();
                    }
                    else
                    {
                        adventure_window = std::make_shared<AdventureWindow>(hInstance);
                        adventure_window->create_dialog();
                        adventure_window->show_window();
                    }
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
                        snakes_demo = std::make_shared<SnakesDemo>(hInstance);
                        snakes_demo->create_window();
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
