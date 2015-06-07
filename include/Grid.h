#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

#include "My_Sprite.h"
#include "Sprite_Creator.h"
#include "Tile.h"



class Grid
{
public:
    Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app);
    virtual ~Grid() = default;
    void loadFiles();
    //get tile at position
    Tile &operator()(size_t x, size_t y);
    void draw();

private:
    std::vector<std::vector<Tile> > m_grid;
	std::vector<Resource> m_resource;
    sf::View *m_view1;
    sf::RenderWindow *m_app;
    Sprite_Creator m_sprite_creator1;
    Clock clock1;
    Time time1;
};

