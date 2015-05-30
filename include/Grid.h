#ifndef GRID_H
#define GRID_H

#include <vector>

#include <stdlib.h>

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

struct Tile
{
    int type;
    int random_pattern;
    int influence_point;
    int x_pos;
    int y_pos;
    int height;
    bool has_citizen;
    bool is_city;
    int citizen_id;
    int zone;
    bool passing_trought;
    Owner_enum owner;
    Ressources_type_enum ressource_type;

};

class Grid
{
public:
    Grid(unsigned int width, unsigned int heigth);
    virtual ~Grid();
    Grid(const Grid& other);
    //get tile at position
    struct Tile &operator()(size_t x, size_t y);
protected:
private:
        std::vector<std::vector<Tile> > grid;

};

#endif // GRID_H
