#include "Window.hpp"

std::unordered_map<HWND, std::shared_ptr<Window>> Window::instances;

Window::Window(HINSTANCE hInstance) :
    hInstance(hInstance)
{
}

Window::~Window()
{
}

void Window::register_window(HWND hwnd, Window* window)
{
    instances[hwnd] = window->shared_from_this();
    window->hwnd = hwnd;
}

std::shared_ptr<Window> Window::lookup_window(HWND hwnd)
{
    auto iter = instances.find(hwnd);

    if (iter == instances.end())
        return nullptr;
    else
        return iter->second;
}

void Window::unregister_window(HWND hwnd)
{
    auto iter = instances.find(hwnd);

    if (iter != instances.end())
    {
        iter->second->hwnd = NULL;
        instances.erase(iter);
    }
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
