#include <stdexcept>
#include <vector>
#include <array>
#include "SnakesDemo.hpp"
#include "GraphPaper.hpp"

char const* SnakesDemo::window_class_name = "SnakesDemo";

SnakesDemo::SnakesDemo(HINSTANCE hInstance) :
    PlainWindow(hInstance)
{
    Color bg_low = {70.0 / 256, 40.0 / 256, 5.0 / 256};  // Brown
    Color bg_high = {110.0 / 256, 80.0 / 256, 6.0 / 256}; // Tan
    auto background = std::make_shared<Texture>(bg_low, bg_high);
    vertex_grid = new VertexGrid(50, 40, background);
}

void SnakesDemo::create_window()
{
    if (!CreateWindowEx(
            WS_EX_CLIENTEDGE,
            window_class_name,
            "Sandpile View",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
            NULL,
            NULL,
            hInstance,
            this))
    {
        MessageBox(NULL, "SnakesDemo window creation failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        throw std::runtime_error("SnakesDemo window registration failed.");
    }
}

void SnakesDemo::register_window_class(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = PlainWindow::WndProc_static;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = window_class_name;
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "SnakesDemo window class registration failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        throw std::runtime_error("SnakesDemo window class registration failed.");
    }
}


LRESULT SnakesDemo::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			if(!SetTimer(hwnd, timer_id, timer_ms, nullptr))
				MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            break;
		}
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, TRUE);
            break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

            RECT rcClient;
			GetClientRect(hwnd, &rcClient);

            DrawScene(hdc, rcClient);

			EndPaint(hwnd, &ps);
            break;
		}
		case WM_TIMER:
		{
			RECT rcClient;
			HDC hdc = GetDC(hwnd);

			GetClientRect(hwnd, &rcClient);

            snakes.step_animation(timer_ms);

            DrawScene(hdc, rcClient);

			ReleaseDC(hwnd, hdc);
		}
		break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
		case WM_DESTROY:
			KillTimer(hwnd, timer_id);
		break;
		default:
			return PlainWindow::WndProc(msg, wParam, lParam);
	}
	return 0;
}

void SnakesDemo::DrawScene(HDC hdc, RECT const& rcClient)
{
    // Handle window size changed.
    if (!EqualRect(&rcClient, &old_size))
    {
        old_size = rcClient;
        vertex_grid->resize(rcClient);
    }

    // Set up double buffering.  TODO: don't create new every frame.
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rcClient.right, rcClient.bottom);
    HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

    // Not needed when the scene background covers whole client area.
    //FillRect(hdcBuffer, &rcClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

    GraphPaper graph_paper(rcClient);

    // Draw scene objects.
    vertex_grid->draw(hdcBuffer);
    graph_paper.draw(hdcBuffer);

    snakes.draw(hdcBuffer);

    // Write buffer to screen.
    BitBlt(hdc, 0, 0, rcClient.right, rcClient.bottom, hdcBuffer, 0, 0, SRCCOPY);

    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteDC(hdcBuffer);
    DeleteObject(hbmBuffer);
}
