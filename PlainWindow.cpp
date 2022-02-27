#include "PlainWindow.hpp"

PlainWindow::PlainWindow(HINSTANCE hInstance) :
    Window(hInstance)
{

}

LRESULT CALLBACK PlainWindow::WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;

    if (msg == WM_NCCREATE)
    {
        auto create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
        Window::register_window(hwnd, reinterpret_cast<Window*>(
                create_struct->lpCreateParams));
    }

    if (auto found_window = Window::lookup_window(hwnd))
    {
        result = std::dynamic_pointer_cast<PlainWindow>(
                found_window)->WndProc(msg, wParam, lParam);
    }
    else
        result = DefWindowProc(hwnd, msg, wParam, lParam);

    if (msg == WM_NCDESTROY)
        Window::unregister_window(hwnd);

    return result;
}


LRESULT PlainWindow::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
