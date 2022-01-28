#include <windows.h>
#include "SandpileView.hpp"
#include "LauncherWindow.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
    //SandpileView sandpile_view(hInstance);
    //sandpile_view.show_window(nCmdShow);
    LauncherWindow launcher(hInstance);
    return launcher.show_dialog();

    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
