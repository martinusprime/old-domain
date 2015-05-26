#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}
void Menu::init(RenderWindow *app_get, View *view1_get)
{
    app = app_get;
    view1 = view1_get;
    sprite.init(app, "ressources/menu_background.png", view1);
    text1.init(app, "Ton puissant Royaume", 24, 0);
}

void Menu::draw()
{
    text1.draw(0, 0, 22);
    sprite.draw(0, 0);
}

void Menu::update()
{
}
