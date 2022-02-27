#pragma once

#include <windows.h>

#include <memory>
#include <unordered_map>

class Window :
    public std::enable_shared_from_this<Window> // Note: must be public
{
private:
    static std::unordered_map<HWND, std::shared_ptr<Window>> instances;

protected:
    HWND hwnd = 0;
    HINSTANCE hInstance;

    static std::shared_ptr<Window> lookup_window(HWND hwnd);
    static void register_window(HWND hwnd, Window* window);
    static void unregister_window(HWND hwnd);

public:
    Window(HINSTANCE hInstance);
    virtual ~Window() = 0;
    void show_window(int nCmdShow = SW_SHOWNORMAL);
    bool is_open() const;
    void set_foreground();
};


