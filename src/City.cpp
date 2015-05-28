#include "City.h"

City::City()
{
    //ctor
}

City::~City()
{
    //dtor
}

void City::init(RenderWindow *app_get, View *view_get, int x_get, int y_get, int tile_size_x_get, int tile_size_y_get)
{
    app = app_get;
    view1 = view_get;
    tile_size_x = tile_size_x_get;
    tile_size_y = tile_size_y_get;
    sprite.init(app, "ressources/city_tile.png", view1);
    x = x_get;
    y = y_get;
    name.init(app, "lolville", 10,  0);

}

void City::draw()
{
    sprite.draw(( x - y) * (tile_size_x / 2), (x +y - 2) * (tile_size_y / 2));
    name.draw(( x - y)  * (tile_size_x / 2), ( x + y - 2)  * (tile_size_y / 2) - 10, 10);
}
