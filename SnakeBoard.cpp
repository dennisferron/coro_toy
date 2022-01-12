#include "SnakeBoard.hpp"

SnakeBoard::SnakeBoard()
{
    std::vector<std::pair<Color, Color>> sn_bk = {
            {{0.5, 0.1, 0.1}, {0.0, 0.8, 0.0}},
            {{255, 132, 5}, {255, 247, 237}},
            {{43, 112, 186}, {16, 34, 54}},
            {{0, 0, 0}, {100, 60, 60}},
    };

    for (std::size_t i=0; i<4; i++)
    {
        std::size_t c = i % sn_bk.size();
        Color const& sn_low = sn_bk[c].first;
        Color const& sn_high = sn_bk[c].second;
        auto sn_texture = std::make_shared<Texture>(sn_low, sn_high);
        snakes.push_back(Snake(sn_texture));
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
