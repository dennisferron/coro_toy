#pragma once

#include <windows.h>

#include <memory>
#include <unordered_map>

class Window : public std::enable_shared_from_this<Window>
{
private:
    static std::unordered_map<HWND, std::shared_ptr<Window>> instances;

protected:
    HWND hwnd = 0;

    static LRESULT CALLBACK WndProc_static(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

    virtual LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam);

public:
    void show_window(int nCmdShow = SW_SHOWNORMAL);
    bool is_open() const;
    void set_foreground();

    std::shared_ptr<Window> get_ptr();
};


