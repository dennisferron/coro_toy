#pragma once

#include "Texture.hpp"

#include <windows.h>
#include <vector>
#include <memory>

class VertexGrid
{
private:
    std::size_t const num_vert_cols;
    std::size_t const num_vert_rows;
    std::size_t const num_vertices;
    std::vector<TRIVERTEX> vertices;
    std::vector<LONG> indices;

    std::shared_ptr<Texture> texture;

    std::size_t get_index(std::size_t col, std::size_t row)
    {
        return row * num_vert_cols + col;
    }

    static LONG scale(LONG len, std::size_t numerator, std::size_t denominator)
    {
        return ::MulDiv(len, numerator, denominator);
    }

    LONG get_y(std::size_t row, RECT const& rect) const
    {
        return scale(rect.bottom-rect.top, row, num_vert_rows - 1)
               + rect.top;
    }

    LONG get_x(std::size_t col, RECT const& rect) const
    {
        return scale(rect.right-rect.left, col, num_vert_cols - 1)
               + rect.left;
    }

    void generate_vertex(std::size_t col, std::size_t row);
    void generate_vertices();
    void add_triangle(LONG a, LONG b, LONG c);
    void generate_tile(std::size_t col, std::size_t row);
    void generate_indices();

    void update_vertex_position(std::size_t col, std::size_t row, RECT const& rect);

    void update_colors();

public:
    VertexGrid(std::size_t const num_cols, std::size_t const num_rows,
           std::shared_ptr<Texture> texture);
    void resize(RECT const& rect);
    void draw(HDC hdc);
};
