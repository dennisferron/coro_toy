#pragma once

#include "SnakesDemo.hpp"
#include "AdventureWindow.hpp"

#include <memory>

class LauncherWindow : public DialogWindow
{
private:
    std::shared_ptr<SnakesDemo> snakes_demo;
    std::shared_ptr<AdventureWindow> adventure_window;

    INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) override;

public:
    explicit LauncherWindow(HINSTANCE hInstance);
    int create_dialog();
};
