#include "Snake.hpp"

Snake::Snake(std::shared_ptr<Texture> texture) :
    texture(texture)
{
}

void Snake::draw(HDC hdc)
{
    RECT rect = { 10, 20, 410, 80 };

    double scale_width = 10;
    double scale_height = 10;

    bool should_offset = false;

    for (double x = rect.left; x < rect.right; x+=scale_width)
    {
        should_offset = !should_offset;
        for (double y=rect.top; y<rect.bottom; y+=scale_height)
        {
            Color scale_color = texture->color_at(x, y);
            int r = scale_color.red_int();
            int g = scale_color.green_int();
            int b = scale_color.blue_int();

            Color line_color = scale_color.fade_to({0,0,0}, 0.15);
            int r2 = line_color.red_int();
            int g2 = line_color.green_int();
            int b2 = line_color.blue_int();

            //Brush and Pen colours
            SelectObject(hdc, GetStockObject(DC_BRUSH));
            SetDCBrushColor(hdc, RGB(r,g,b));
            SelectObject(hdc, GetStockObject(DC_PEN));
            SetDCPenColor(hdc, RGB(r2,g2,b2));

            double y_offset = should_offset ? 3.5 : -3.5;

            Ellipse(hdc, x-7, y_offset+y-7, x+7, y_offset+y+7);
        }
    }
}