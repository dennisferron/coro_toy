#include "SnakeBoard.hpp"
#include "Snake.hpp"

SnakeBoard::SnakeBoard()
{
    for (int i=0; i<num_cols; i++)
        for (int j=0; j<num_rows; j++)
            board[i][j] = 0;

    std::vector<std::pair<Color, Color>> sn_bk = {
            {{0.5, 0.1, 0.1}, {0.0, 0.8, 0.0}},
            {{255, 132, 5}, {255, 247, 237}},
            {{43, 112, 186}, {16, 34, 54}},
            {{0, 0, 0}, {100, 60, 60}},
    };

    for (std::size_t i=1; i<=4; i++)
    {
        std::size_t c = i % sn_bk.size();
        Color const& sn_low = sn_bk[c].first;
        Color const& sn_high = sn_bk[c].second;
        auto sn_texture = std::make_shared<Texture>(sn_low, sn_high);
        snakes.push_back(Snake(this, i, sn_texture,
                               {(double)i*3, (double)i*2}));
    }
}

void SnakeBoard::draw(HDC hdc)
{
    for (auto& snake : snakes)
        snake.draw(hdc);
}

void SnakeBoard::step_animation(unsigned int delta_ms)
{
    for (auto& snake : snakes)
        snake.step_animation(delta_ms);
}

bool SnakeBoard::request_cell(Vector2 pos, int id)
{
    int col = round(pos.x);
    int row = round(pos.y);

    if (col < 0 || col >= num_cols ||
        row < 0 || row >= num_rows)
            return false;
    else if (board[col][row] == id)
        return true; // allow self-intersection
    else if (board[col][row] > 0)
        return false;
    else
    {
        board[col][row] = id;
        return true;
    }
}

void SnakeBoard::return_cell(Vector2 pos, int id)
{
    int col = round(pos.x);
    int row = round(pos.y);

    if (col < 0 || col >= num_cols ||
        row < 0 || row >= num_rows)
    {
        throw std::logic_error("return_cell: row or col out of range.");
    }
    else if (board[col][row] == 0)
    {
        //throw std::logic_error("return_cell: cell is already empty.");
    }
    else if (board[col][row] != id)
    {
        //throw std::logic_error("return_cell: cell belongs to different snake.");
    }
    else
    {
        board[col][row] = 0;
    }
}
