#ifndef GRID_H
#define GRID_H

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

struct Tile
{
    int type;
    int random_pattern;
    int influence_point;
    int x_pos;
    int y_pos;
    int height;
    bool is_city;
    int citizen_id;
    int zone;
    bool passing_trought;
    Owner_enum owner;
    Ressources_type_enum ressource_type;
    static My_Sprite tile_sprite[10];
    static My_Sprite influence_sprite;
    static const Tile_dimension tile_size;

    void draw(int type , int x_pos, int y_pos);
};

class Grid
{
public:
    Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app);
    virtual ~Grid();
    Grid(const Grid& other);
    void loadFiles();
    //get tile at position
    struct Tile &operator()(size_t x, size_t y);
    void draw();
protected:
private:

	std::vector<std::vector<Tile> > m_grid;
	std::vector<Resource> m_resource;
    sf::View *m_view1;
    sf::RenderWindow *m_app;
    Sprite_Creator m_sprite_creator1;

    Clock clock1;
    Time time1;
};

#endif // GRID_H
