#include "Snake.hpp"
#include "Bezier.hpp"

Snake::Snake(std::shared_ptr<Texture> texture) :
    texture(texture)
{
    double right = scale_cols*scale_spacing*0.6;
    double bottom = scale_cols*scale_spacing*0.6;
    splines.push_back(
        Bezier({0, 0}, {right/2,0}, {right/2,bottom/2}));
    splines.push_back(
        Bezier({right/2,bottom/2}, {right/2,bottom},{right,bottom}));
}

Vector2 Snake::transform(Vector2 in) const
{
    Vector2 wr = transform_wrap(in);
    Vector2 bz = transform_bezier(wr);

    //return { in.x, in.y+20};
    //return { wr.x, wr.y+20};
    return { bz.x, bz.y };

    if (phase < 0.5)
    {
        double t = 2*phase;
        return {lerp(in.x, wr.x, t), lerp(in.y, wr.y, t)};
    }
    else
    {
        double t = 2*(phase-0.5);
        return {lerp(wr.x, bz.x, t), lerp(wr.y, bz.y, t)};
    }
}

Vector2 Snake::transform_wrap(Vector2 in) const
{
    double y_scaled = in.y / (scales_height/2); // +/-1.0
    constexpr double PI = 3.14159265;
    double theta = y_scaled * PI * 0.5;
    double radius = scales_height / PI;  // stretched over half the circumference
    double y_new = sin(theta) * radius;

    return { in.x, y_new};
}

Vector2 Snake::transform_tail(Vector2 in) const
{
    double s = in.x / scales_width;
    constexpr double tail_section = 0.2;
    if (s < tail_section)
    {

        double y2 = in.y * s * (1.0/tail_section);
    }
    else
    {
        return in;
    }
}

Vector2 Snake::transform_bezier(Vector2 in) const
{
    double s = (in.x / scales_width);
    double s_all = s * splines.size();
    std::size_t index = static_cast<std::size_t>(s_all);
    double s_frac = s_all - index;

    Bezier const& bez = splines[index];
    Vector2 bz_org = bez.pos_at(s_frac);
    Vector2 bz_ofs = in.y * bez.normal_at(s_frac);
    Vector2 bz_pos = bz_org + bz_ofs;

    return { bz_pos.x, bz_pos.y };
}

void Snake::draw(HDC hdc)
{
    bool should_offset = false;

    for (int col = 0; col < scale_cols; col++)
    {
        double x = col * scale_spacing;
        should_offset = !should_offset;
        for (int row = 0; row < scale_rows; row++)
        {
            double y = row * scale_spacing - scales_height/2;
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

            double y_offset = should_offset ? scale_radius/2 : -scale_radius/2;

            // The bottom row of scales stands out too much because no
            // further row overlaps them. Tweaking the offset works to
            // smooth the outline because it pushes the bumpy side into
            // the more squashed portion of the sin(theta) transform.
            y_offset += scale_radius/2;

            Vector2 pos = transform({x, y+y_offset});
            Vector2 top_left = { pos.x-scale_radius, pos.y-scale_radius };
            Vector2 bottom_right = {pos.x+scale_radius, pos.y+scale_radius};

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
    constexpr double period_seconds = 4.0;
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
