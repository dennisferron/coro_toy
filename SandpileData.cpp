#include "SandpileData.hpp"

SandpileData::SandpileData(std::size_t const num_cols, std::size_t const num_rows) :
    num_cols(num_cols), num_rows(num_rows), data(num_cols*num_rows)
{
}

int& SandpileData::at(std::size_t col, std::size_t row)
{
    return data[row*num_cols + col];
}

int const& SandpileData::at(std::size_t col, std::size_t row) const
{
    return data[row*num_cols + col];
}
