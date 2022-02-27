#include "AdventureWindow.hpp"

#include "resource.h"

#include <stdexcept>
#include <vector>
#include <array>

AdventureWindow::AdventureWindow(HINSTANCE hInstance) :
        DialogWindow(hInstance)
{
}

int AdventureWindow::create_dialog()
{
    return DialogBoxParam(
            hInstance,
            MAKEINTRESOURCE(IDD_ADVENTURE),
            NULL,
            DialogWindow::DlgProc_static,
            reinterpret_cast<LPARAM>(this)
    );
}

INT_PTR AdventureWindow::DlgProc(UINT msg, WPARAM wParam, LPARAM lParam)
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
