#include <stdexcept>
#include <vector>
#include <array>
#include "SandpileView.hpp"

char const* SandpileView::window_class_name = "SandpileView";

SandpileView::SandpileView(HINSTANCE hInstance) :
        vertex_grid()
{
    // TODO: Refactor window class registration into a singleton event.
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
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
        MessageBox(NULL, "SandpileView window class registration failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        throw std::runtime_error("SandpileView window class registration failed.");
    }

    if (!CreateWindowEx(
        WS_EX_CLIENTEDGE,
        window_class_name,
        "Sandpile View",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 320, 240,
        NULL,
        NULL,
        hInstance,
        this))
    {
        MessageBox(NULL, "SandpileView window creation failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        throw std::runtime_error("SandpileView window registration failed.");
    }

    //SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
}

void SandpileView::show_window(int nCmdShow)
{
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
}

LRESULT CALLBACK SandpileView::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CREATE:
        {
            auto create_struct = reinterpret_cast<CREATESTRUCT*>(lParam);
            void* user_data = create_struct->lpCreateParams;
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(user_data));
            auto view_obj = reinterpret_cast<SandpileView*>(user_data);
            view_obj->hwnd = hwnd;
            return view_obj->WndProc(msg, wParam, lParam);
        }
        default:
        {
            LONG_PTR user_data = GetWindowLongPtr(hwnd, GWLP_USERDATA);

            // Messages like WM_GETMINMAXINFO may come in before
            // we have had a chance to set the user data.
            if (user_data)
            {
                auto view_obj = reinterpret_cast<SandpileView*>(user_data);
                return view_obj->WndProc(msg, wParam, lParam);
            }
            else
            {
                return DefWindowProc(hwnd, msg, wParam, lParam);
            }
        }
    }
}


LRESULT SandpileView::WndProc(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch(msg)
	{
		case WM_CREATE:
		{
			if(!SetTimer(hwnd, timer_id, 50, nullptr))
				MessageBox(hwnd, "Could not SetTimer()!", "Error", MB_OK | MB_ICONEXCLAMATION);
            break;
		}
		case WM_CLOSE:
			DestroyWindow(hwnd);
    		break;
        case WM_SIZE:
            InvalidateRect(hwnd, NULL, TRUE);
            break;
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);

            RECT rcClient;
			GetClientRect(hwnd, &rcClient);

            if (!vertex_grid)
                vertex_grid = new VertexGrid(5, 4);

            vertex_grid->draw(hdc, rcClient);

            constexpr int num_vertices = 5;
            TRIVERTEX vertex[num_vertices];

            {
                // Create an array of TRIVERTEX structures that describe
                // positional and color values for each vertex. For a rectangle,
                // only two vertices need to be defined: upper-left and lower-right.
                vertex[3].x = 10;
                vertex[3].y = 10;
                vertex[3].Red = 0xd000;
                vertex[3].Green = 0xd000;
                vertex[3].Blue = 0x3000;
                vertex[3].Alpha = 0x0000;

                vertex[4].x = 30;
                vertex[4].y = 30;
                vertex[4].Red = 0x8000;
                vertex[4].Green = 0x8000;
                vertex[4].Blue = 0x0000;
                vertex[4].Alpha = 0x0000;

                // Create a GRADIENT_RECT structure that
                // references the TRIVERTEX vertices.
                GRADIENT_RECT gRect;
                gRect.UpperLeft = 3;
                gRect.LowerRight = 4;

                // Draw a shaded rectangle.
                GradientFill(hdc, vertex, num_vertices, &gRect, 1, GRADIENT_FILL_RECT_V);
            }
            {
                // Create an array of TRIVERTEX structures that describe
                // positional and color values for each vertex.
                vertex[0].x     = 150;
                vertex[0].y     = 0;
                vertex[0].Red   = 0xff00;
                vertex[0].Green = 0x8000;
                vertex[0].Blue  = 0x0000;
                vertex[0].Alpha = 0x0000;

                vertex[1].x     = 0;
                vertex[1].y     = 150;
                vertex[1].Red   = 0x9000;
                vertex[1].Green = 0x0000;
                vertex[1].Blue  = 0x9000;
                vertex[1].Alpha = 0x0000;

                vertex[2].x     = 300;
                vertex[2].y     = 150;
                vertex[2].Red   = 0x9000;
                vertex[2].Green = 0x0000;
                vertex[2].Blue  = 0x9000;
                vertex[2].Alpha = 0x0000;

// Create a GRADIENT_TRIANGLE structure that
// references the TRIVERTEX vertices.
                GRADIENT_TRIANGLE gTriangle;
                gTriangle.Vertex1 = 0;
                gTriangle.Vertex2 = 1;
                gTriangle.Vertex3 = 2;

// Draw a shaded triangle.
                GradientFill(hdc, vertex, num_vertices, &gTriangle, 1, GRADIENT_FILL_TRIANGLE);
            }

			EndPaint(hwnd, &ps);
            break;
		}
		case WM_TIMER:
		{
			RECT rcClient;
			HDC hdc = GetDC(hwnd);

			GetClientRect(hwnd, &rcClient);

			//UpdateBall(&rcClient);
			//DrawBall(hdc, &rcClient);

			ReleaseDC(hwnd, hdc);
		}
		break;
		case WM_DESTROY:
			KillTimer(hwnd, timer_id);

			//DeleteObject(g_hbmBall);
			//DeleteObject(g_hbmMask);

			PostQuitMessage(0);
		break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
