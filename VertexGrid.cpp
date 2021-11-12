#include "VertexGrid.hpp"

void VertexGrid::generate_vertex(std::size_t col, std::size_t row)
{
    static int count = 0;
    ++count;
    TRIVERTEX vertex;
    vertex.x = get_x(col);
    vertex.y = get_y(row);
    vertex.Alpha = 0x0000;
    vertex.Red = count%2? 0 : lerp(0xFF00, col, all_cols);
    vertex.Green = count%3? 0 : lerp(0xFF00, row, all_rows);
    vertex.Blue = count%4==0? 0: lerp(0xFF00, row+col, all_rows+all_cols);
    vertices.push_back(vertex);
}

void VertexGrid::generate_vertices()
{
    for (std::size_t row=0; row<all_rows; row++)
    {
        for (std::size_t col=0; col<all_cols; col++)
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
    for (std::size_t row=0; row<all_rows-1; row++)
    {
        for (std::size_t col=0; col<all_cols-1; col++)
        {
            generate_tile(col, row);
        }
    }
}

VertexGrid::VertexGrid(std::size_t const data_cols, std::size_t const data_rows) :
data_cols(data_cols), data_rows(data_rows),
all_cols(2*data_cols+1), all_rows(2*data_rows+1),
num_vertices(all_cols * all_rows)
{
    generate_vertices();
    generate_indices();
}

void VertexGrid::draw(HDC hdc, RECT const& rect)
{
    if (!EqualRect(&rect,&this->rect))
        VertexGrid::update_mesh_positions(rect);

    GradientFill(
            hdc,
            &vertices[0],
            vertices.size(),
            &indices[0],
            indices.size()/3,
            GRADIENT_FILL_TRIANGLE);
}

void VertexGrid::update_mesh_positions(RECT const& rect)
{
    this->rect = rect;

    for (std::size_t row=0; row<all_rows; row++)
    {
        for (std::size_t col=0; col<all_cols; col++)
        {
            update_vertex_position(col, row);
        }
    }
}

void VertexGrid::update_vertex_position(std::size_t col, std::size_t row)
{
    auto index = get_index(col, row);
    TRIVERTEX& vertex = vertices[index];
    vertex.x = get_x(col);
    vertex.y = get_y(row);
}
