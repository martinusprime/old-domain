#include "Grid.h"

Grid::Grid(unsigned int width, unsigned int heigth)
: grid(width, std::vector<Tile>(heigth))
{
    //ctor
}

Grid::~Grid()
{
    //dtor
}

Grid::Grid(const Grid& other)
{
    //copy ctor
}

Tile &Grid::operator()(size_t x, size_t y)
{
    return grid.at(x).at(y);
}
