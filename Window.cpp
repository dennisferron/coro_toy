#include "Window.hpp"

std::unordered_map<HWND, std::shared_ptr<Window>> Window::instances;

LRESULT CALLBACK Window::WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        auto create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
        auto window = reinterpret_cast<Window*>(create_struct->lpCreateParams);
        instances[hwnd] = window->shared_from_this();
        int x = instances[hwnd].use_count();
        window->hwnd = hwnd;
    }

    auto window_iter = instances.find(hwnd);

    if (window_iter == instances.end())
        return DefWindowProc(hwnd, msg, wParam, lParam);
    else
    {
        Window& window = *(window_iter->second);
        LRESULT result = window.WndProc(msg, wParam, lParam);

        if (msg == WM_NCDESTROY)
        {
            instances.erase(window_iter);
            window.hwnd = NULL;
        }

        return result;
    }
}


LRESULT Window::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Window::show_window(int nCmdShow)
{
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

bool Window::is_open() const
{
    return hwnd != NULL;
}

void Window::set_foreground()
{
    ::SetForegroundWindow(hwnd);
}

std::shared_ptr<Window> Window::get_ptr()
{
    return shared_from_this();
}
