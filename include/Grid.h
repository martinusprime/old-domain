#pragma once

#include <stdlib.h>
#include <vector>
#include <string>

#include "My_Sprite.h"
#include "Sprite_Creator.h"

enum Owner_enum
{
    YOU,
    PLAYER2,
    PLAYER3
};

enum Ressources_type_enum
{
    RSC_NO,
    RSC_WOOD,
    RSC_IRON
};

struct Tile_dimension
{
    int x;
    int y;
};


struct Resource
{
	int type;
	int flexibility;
	int solidity;
	string name;
	My_Sprite sprite;
};

class Tile
{
public:
    void draw();

    int m_type;
    int random_pattern;
    int influence_point;
    int m_x_pos;
    int m_y_pos;
    int height;
    bool is_city;
    int citizen_id;
    int zone;
    bool passing_through;
    Owner_enum owner;
    Ressources_type_enum ressource_type;
    static vector<My_Sprite> tile_sprites;
    static vector<My_Sprite> influence_sprites;
    static const Tile_dimension tile_size;
};

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

