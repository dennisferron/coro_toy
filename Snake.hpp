#pragma once

#include "Texture.hpp"
#include "Vector2.hpp"
#include "Bezier.hpp"

#include <windows.h>

#include <memory>
#include <deque>
#include <vector>

class SnakeBoard;

class Snake
{
public:
    static constexpr double square_size = 40;

private:
    SnakeBoard* board;
    int id;
    std::shared_ptr<Texture> texture;
    std::vector<Bezier> splines;
    double phase = 0.0;
    double phase_dir = 1.0;

    Vector2 tail_pos;
    std::deque<Vector2> heading;
    Vector2 old_tail_hdg;

    static constexpr double scale_spacing = 6.0;
    static constexpr double scale_radius = 0.8*scale_spacing;
    static constexpr int scale_rows = 4;
    static constexpr int scale_cols = 100;
    static constexpr double scales_height = scale_rows * scale_spacing;
    static constexpr double scales_width = scale_cols * scale_spacing;

    Vector2 transform(Vector2 in) const;

    Vector2 transform_wrap(Vector2 in) const;
    Vector2 transform_bezier(Vector2 in) const;
    Vector2 transform_tail(Vector2 in) const;

    void reticulate_splines();

    Vector2 get_board_square(std::size_t index) const;
    Vector2 get_head_square(Vector2 dir) const;

public:
    Snake(SnakeBoard* board, int id, std::shared_ptr<Texture> texture, Vector2 pos);
    void draw(HDC hdc);
    void step_animation(unsigned int delta_ms);
    void move(Vector2 const& dir);
};


