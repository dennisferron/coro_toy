#include "Snake.hpp"

Snake::Snake(std::shared_ptr<Texture> texture) :
    texture(texture)
{
}

Vector2 Snake::transform(Vector2 in) const
{
    // Actual extreme values are top is 9.5 and bottom is 90.5
    // however since bottom is draw last more of the ellipse is visible.
    // Can mitigate that by skewing window over scale texture by using 80.
    double height = 80 - 10;
    double y_origin = 10 + height/2;
    double y_centered = in.y - y_origin;
    double y_scaled = y_centered / (height/2); // +/-1.0
    constexpr double PI = 3.14159265;
    double theta = y_scaled * PI * 0.5;
    double radius = height / PI;  // stretched over half the circumference
    double y_new = sin(theta) * radius + y_origin;
    //double y_new = (1.0 - abs(y_scaled)) * y_centered + y_origin;
    return { in.x, lerp(in.y, y_new, phase) };
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

            Vector2 top_left = transform({ x-7, y_offset+y-7 });
            Vector2 bottom_right = transform({x+7, y_offset+y+7});

            Ellipse(hdc,
                    top_left.x,
                    top_left.y,
                    bottom_right.x,
                    bottom_right.y);
        }
    }
}

void Snake::step_animation(unsigned int delta_ms)
{
    constexpr double period_seconds = 1.0;
    double delta_phase = (delta_ms / 1000.0) / period_seconds;
    phase += phase_dir * delta_phase;
    if (phase_dir > 0.0 && phase > 1.0)
    {
        phase = 1.0;
        phase_dir = -1.0;
    }
    else if (phase_dir < 0.0 && phase < 0.0)
    {
        phase = 0.0;
        phase_dir = 1.0;
    }
}
