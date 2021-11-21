#pragma once

#include "SandpileData.hpp"

#include <windows.h>
#include <vector>

class VertexGrid
{
private:
    std::size_t const data_cols;
    std::size_t const data_rows;
    std::size_t const all_cols;
    std::size_t const all_rows;
    std::size_t const num_vertices;
    std::vector<TRIVERTEX> vertices;
    std::vector<LONG> indices;

    RECT rect;

    std::size_t get_index(std::size_t col, std::size_t row)
    {
        return row * all_cols + col;
    }

    static LONG lerp(LONG len, std::size_t numerator, std::size_t denominator)
    {
        return ::MulDiv(len, numerator, denominator);
    }

    LONG get_y(std::size_t row) const
    {
        return lerp(rect.bottom-rect.top, row, all_rows-1)
               + rect.top;
    }

    LONG get_x(std::size_t col) const
    {
        return lerp(rect.right-rect.left, col, all_cols-1)
               + rect.left;
    }

    void generate_vertex(std::size_t col, std::size_t row);
    void generate_vertices();
    void add_triangle(LONG a, LONG b, LONG c);
    void generate_tile(std::size_t col, std::size_t row);
    void generate_indices();

    void update_mesh_positions(RECT const& rect);
    void update_vertex_position(std::size_t col, std::size_t row);

public:
    VertexGrid(std::size_t const data_cols, std::size_t const data_rows);
    void draw(HDC hdc, RECT const& rect);
    void update_colors(SandpileData const& data);
};
