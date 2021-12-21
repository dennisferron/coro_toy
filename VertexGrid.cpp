#include "VertexGrid.hpp"
#include "Perlin.hpp"
#include "WindowsErrorException.hpp"

#include <sstream>

void VertexGrid::generate_vertex(std::size_t col, std::size_t row)
{
    static int count = 0;
    ++count;
    TRIVERTEX vertex;
    vertex.x = 0;
    vertex.y = 0;
    vertex.Alpha = 0x0000;
    vertex.Red = 0;
    vertex.Green = 0;
    vertex.Blue = 0;
    vertices.push_back(vertex);
    positions.push_back({0, 0});
}

void VertexGrid::generate_vertices()
{
    for (std::size_t row=0; row < num_vert_rows; row++)
    {
        for (std::size_t col=0; col < num_vert_cols; col++)
        {
            generate_vertex(col, row);
        }
    }
}

void VertexGrid::add_triangle(LONG a, LONG b, LONG c)
{
    indices.push_back(a);
    indices.push_back(b);
    indices.push_back(c);
}

void VertexGrid::generate_tile(std::size_t col, std::size_t row)
{
    auto tl = get_index(col, row);
    auto tr = get_index(col+1, row);
    auto bl = get_index(col, row+1);
    auto br = get_index(col+1, row+1);

    /*
           0   1
        0 +---*---+
          | / | \ |
        1 *---+---*
          | \ | / |
          +---*---+
     */

    if ((col+row)%2==0)
    {
        /*
        tl     tr
          +---*
          | / |
          *---+
        bl     br
         */
        add_triangle(tl, tr, bl);
        add_triangle(br, bl, tr);
    }
    else
    {
        /*
        tl     tr
          +---*
          | \ |
          *---+
        bl     br
         */
        add_triangle(tl, br, bl);
        add_triangle(br, tl, tr);
    }
}

void VertexGrid::generate_indices()
{
    for (std::size_t row=0; row < num_vert_rows - 1; row++)
    {
        for (std::size_t col=0; col < num_vert_cols - 1; col++)
        {
            generate_tile(col, row);
        }
    }
}

VertexGrid::VertexGrid(std::size_t const num_cols, std::size_t const num_rows,
                       std::shared_ptr<Texture> texture) :
        num_vert_cols(2 * num_cols + 1), num_vert_rows(2 * num_rows + 1),
        num_vertices(num_vert_cols * num_vert_rows),
        texture(texture)
{
    generate_vertices();
    generate_indices();
}

void VertexGrid::draw(HDC hdc)
{
    bool result = GradientFill(
            hdc,
            &vertices[0],
            vertices.size(),
            &indices[0],
            indices.size()/3,
            GRADIENT_FILL_TRIANGLE);

    if (!result)
    {
        throw WindowsErrorException::FromGetLastError("GradientFill returned false");
    }
}

void VertexGrid::resize(RECT const& rect)
{
    for (std::size_t row=0; row < num_vert_rows; row++)
    {
        for (std::size_t col=0; col < num_vert_cols; col++)
        {
            update_vertex_position(col, row, rect);
        }
    }

    update_colors();
}

void VertexGrid::update_vertex_position(std::size_t col, std::size_t row, RECT const& rect)
{
    auto index = get_index(col, row);
    TRIVERTEX& vertex = vertices[index];
    Vector2& pos = positions[index];
    vertex.x = pos.x = get_x(col, rect);
    vertex.y = pos.y = get_y(row, rect);
}

void VertexGrid::update_colors()
{
    for (std::size_t i=0; i<vertices.size(); i++)
    {
        auto const& pos = positions[i];
        Color c = texture->color_at(pos.x, pos.y);

        auto& vert = vertices[i];
        vert.Red = static_cast<int>(0xFF00*c.R);
        vert.Green = static_cast<int>(0xFF00*c.G);
        vert.Blue = static_cast<int>(0xFF00*c.B);
    }
}

void VertexGrid::shape()
{
    constexpr double top = 20;
    constexpr double bottom = 50;
    constexpr double height = bottom - top;
    constexpr double middle = top + height/2;

    constexpr double left = 10;
    constexpr double right = 200;
    constexpr double width = right - left;

    auto f = [](double v, double scale)
        { return v<0? std::lerp(0.0, -scale, -v) : std::lerp(0.0, scale, v); };

    for (auto& pos : positions)
    {
        double u = (pos.x - left) / width;
        double v = (pos.y - middle) / (height/2);

        double scale;

        if (u < 0.15)
            scale = 0.30*sqrt(50*u);
        else if (u < 0.3)
            scale = 0.5 + 2.5*(0.3-u);
        else if (u < 0.75)
            scale = 1.0;
        else
            scale = 1.0-3*(u-0.75);

        if (scale < 0.28)
            scale = scale;// 0.28;
        else if (scale > 1.2)
            scale = 1.2;

        pos.y = f(v,scale)*(height/2) + middle;
    }
}

void VertexGrid::wriggle()
{
    for (std::size_t i=0; i<vertices.size(); i++)
    {
        auto const& pos = positions[i];
        auto& vert = vertices[i];
        vert.x = pos.x;
        vert.y = pos.y; // + 2 * sin(0.1*pos.x);
    }
}