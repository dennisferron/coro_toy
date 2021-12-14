#include "VertexGrid.hpp"
#include "Perlin.hpp"

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
    GradientFill(
            hdc,
            &vertices[0],
            vertices.size(),
            &indices[0],
            indices.size()/3,
            GRADIENT_FILL_TRIANGLE);
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
    vertex.x = get_x(col, rect);
    vertex.y = get_y(row, rect);
}

void VertexGrid::update_colors()
{
    for (auto& vert : vertices)
    {
        Color c = texture->color_at(vert.x, vert.y);

        vert.Red = static_cast<int>(0xFF00*c.R);
        vert.Green = static_cast<int>(0xFF00*c.G);
        vert.Blue = static_cast<int>(0xFF00*c.B);
    }
}
