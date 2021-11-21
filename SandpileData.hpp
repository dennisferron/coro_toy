#pragma once

#include <vector>

class SandpileData
{
private:
    std::size_t const num_cols;
    std::size_t const num_rows;
    std::vector<int> data;

public:
    SandpileData(std::size_t const num_cols, std::size_t const num_rows);
    int& at(std::size_t col, std::size_t row);
    int const& at(std::size_t col, std::size_t row) const;
};


