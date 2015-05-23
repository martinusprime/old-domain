#include "Menu.h"

Menu::Menu()
{
    //ctor
}

Menu::~Menu()
{
    //dtor
}
void Menu::init(RenderWindow *app_get)
{
    app = app_get;
    if(!texture.loadFromFile("ressources/menu_background.png"))
    {

    }
    text1.init(app, "Ton puissant Royaume", 24, 0);

    sprite.setTexture(texture);
}

void Menu::draw()
{
    app->draw(sprite);
    text1.draw(500, 500, 25);
}

void Menu::update()
{
}
