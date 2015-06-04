#include "Menu.h"

Menu::Menu(RenderWindow *app, View *view1)
: sprite(app, "ressources/menu_background.png", view1)
{
    m_app = app;
    m_view1 = view1;

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
