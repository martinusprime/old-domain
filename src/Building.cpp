#include "Building.h"

Building::Building()
{
    //ctor
}

Building::~Building()
{
    //dtor
}

void Building::init(RenderWindow *app_get, View *view_get,int type)
{
    app = app_get;
    view1 = view_get;
    sprite.init(app, "ressources/empty.png", view1);
    sprite.add_sprite("bo");
    x = 0;
    y = 0;

}


void Building::draw(int x, int y)
{
    sprite.draw(x, y);
}
