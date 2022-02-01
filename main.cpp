#include <windows.h>
#include "SandpileView.hpp"
#include "LauncherWindow.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    SandpileView::register_window_class(hInstance);
    LauncherWindow launcher(hInstance);
    return launcher.show_dialog();
}
