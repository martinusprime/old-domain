#include "Building.h"

Building::Building()
{
    //ctor
}

Building::~Building()
{
    //dtor
}

void Building::init(RenderWindow *app_get, View *view_get,int type_get)
{
    app = app_get;
    view1 = view_get;
    sprite.init(app, "ressources/empty.png", view1);
    x = 0;
    y = 0;
    type = type_get;

}


void Building::draw(int x_get, int y_get)
{
    sprite.draw(x_get, y_get);
}
