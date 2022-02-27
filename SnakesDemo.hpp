#pragma once

#include "VertexGrid.hpp"
#include "Snake.hpp"
#include "SnakeBoard.hpp"

#include "PlainWindow.hpp"

#include <vector>

class SnakesDemo : public PlainWindow
{
private:
    RECT old_size = {};

    int timer_id = 1; // TODO: Pass per-instance?
    unsigned int timer_ms = 50;

    VertexGrid* vertex_grid = nullptr;
    SnakeBoard snakes;

    static const char* window_class_name;

    void DrawScene(HDC hdc, RECT const& rcClient);

protected:
    LRESULT WndProc(UINT msg, WPARAM wParam, LPARAM lParam) override;

public:
    static void register_window_class(HINSTANCE hInstance);

    explicit SnakesDemo(HINSTANCE hInstance);
    void create_window();
};
