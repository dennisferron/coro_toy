#include <windows.h>
#include "SnakesDemo.hpp"
#include "LauncherWindow.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    SnakesDemo::register_window_class(hInstance);
    //AdventureWindow::
    LauncherWindow launcher(hInstance);
    return launcher.show_dialog();
}
