#include "City.h"

City::City()
{
    //ctor
}

City::~City()
{
    //dtor
}

void City::init(RenderWindow *app_get, View *view_get, int x_get, int y_get)
{
    app = app_get;
    view1 = view_get;
    sprite.init(app, "ressources/city_tile.png", view1);
    x = x_get;
    y = y_get;
    name.init(app, "lolville", 10,  0);

}

void City::draw()
{
    sprite.draw(x * 50 , y * 50);
    name.draw(x * 50, y * 50 - 10, 10);
}
