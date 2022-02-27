#pragma once

#include "DialogWindow.hpp"

class AdventureWindow : public DialogWindow
{
protected:
    INT_PTR DlgProc(UINT msg, WPARAM wParam, LPARAM lParam) override;

public:
    explicit AdventureWindow(HINSTANCE hInstance);
    int create_dialog();
};
