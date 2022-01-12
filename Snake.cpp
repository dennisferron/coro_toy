#include "Snake.hpp"
#include "Bezier.hpp"
#include "SnakeBoard.hpp"

#include <numbers>
#include <random>

Snake::Snake(SnakeBoard* board, std::shared_ptr<Texture> texture, Vector2 pos) :
    board(board), texture(texture), tail_pos(pos)
{
    double right = scale_cols*scale_spacing*0.6;
    double bottom = scale_cols*scale_spacing*0.6;
    splines.push_back(
        Bezier({0, 0}, {right/2,0}, {right/2,bottom/2}));
    splines.push_back(
        Bezier({right/2,bottom/2}, {right/2,bottom},{right,bottom}));

    for (int i=0; i<18; i++)
    {
        heading.push_back({0,0});
    }

    reticulate_splines();
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
    double s_all = s * (splines.size()-1) + phase;
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

            if (col >= 97)
                scale_color = {1.0, 0.0, 0.0};

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
    constexpr double period_seconds = 2.0;
    double delta_phase = (delta_ms / 1000.0) / period_seconds;
    phase += phase_dir * delta_phase;
    if (phase_dir > 0.0 && phase > 1.0)
    {
        phase = 1.0;
        phase_dir = -1.0;

        static std::default_random_engine rnd_eng {};
        static std::uniform_int_distribution<> get_dir {0, 7};

        for (int tries = 0; tries < 6; tries++)
        {
            Vector2 v;
            switch (get_dir(rnd_eng))
            {
                case 0:
                    v = {1, 0};
                    break;
                case 1:
                    v = {-1, 0};
                    break;
                case 2:
                    v = {0, 1};
                    break;
                case 3:
                    v = {0, -1};
                    break;
                default:
                    v = *(heading.end()-1);
            }

            Vector2 next_cell = get_head_square(v);
            if (board->request_cell(next_cell))
            {
                board->return_cell(get_board_square(0));
                move(v);
                phase = 0.0;
                phase_dir = 1.0;
                break;
            }
        }
    }
    else if (phase_dir < 0.0 && phase < 0.0)
    {
        phase = 0.0;
        phase_dir = 1.0;
    }
}

void Snake::move(Vector2 const& dir)
{
    old_tail_hdg = heading.front();
    tail_pos += heading.front();
    heading.pop_front();
    heading.push_back(dir);

    reticulate_splines();
}

void Snake::reticulate_splines()
{
    splines.clear();

    /*
        Initial condition:
            Start p1 in center of the square (0.5, 0.5)
            Back-fill p0 by subtracting half of old heading
            Set p2 by adding half of first heading to p1
        This puts p2 at one of the four sides of the square
        where the first heading was headed, and points the
        tail at the opposite end of the square.
    */
    Vector2 p1 = tail_pos + Vector2 {0.5, 0.5};
    Vector2 p0 = p1 - 0.5 * old_tail_hdg;
    Vector2 p2 = p1 + 0.5 * heading[0];

    /*
        To make the math simpler we calculate control points
        using unit squares and convert to pixel coordinates
        only at the last moment when adding the splines.
    */
    splines.push_back({square_size*p0, square_size*p1, square_size*p2});

    /*
        The initial (zeroth) segment starts from the center point
        of the square at tail_pos and heads to one side of square,
        but subsequent segments of the snake will traverse whole
        squares starting from one side and exiting at another.
     */

    for (std::size_t i = 1; i<heading.size(); i++)
    {
        /*
            First control point, p0, of next segment starts at p2
            of last segment (obviously), recall this is at middle
            of one the four sides where we entered a new square.

            Second control point, p1, continues in the direction
            we entered on. This puts p1 in a position to pull on
            the outside of the curve when the snake changes direction.
            (And if snake doesn't change direction, p1 will be in-line.
            In fact p1 is always in the center of a square regardless.)

            Third control point, p2, arcs towards next heading.  Since
            p1 is always the center of a square, p2 again reaches one
            of the walls of a square after traveling distance 0.5 from
            p1.  Thus setting up initial conditions again for next loop.
         */
        p0 = p2;
        p1 = p0 + 0.5 * heading[i-1];
        p2 = p1 + 0.5 * heading[i];

        splines.push_back({square_size*p0, square_size*p1, square_size*p2});
    }

    // Project head of snake into the last square.
    p0 = p2;
    p1 = p0 + 0.5 * *heading.rbegin();
    p2 = p1 + 0.5 * *heading.rbegin();

    splines.push_back({square_size*p0, square_size*p1, square_size*p2});
}

Vector2 Snake::get_board_square(std::size_t index) const
{
    Vector2 pos = tail_pos;

    for (std::size_t i=0; i<index && i<heading.size(); i++)
        pos += heading[i];

    return pos;
}

Vector2 Snake::get_head_square(Vector2 dir) const
{
    return get_board_square(heading.size()) + dir;
}