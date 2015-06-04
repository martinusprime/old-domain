#pragma once

#include <SFML/Graphics.hpp>
#include "My_Text.h"

#include "My_Sprite.h"
using namespace sf;


class Menu
{
public:
    Menu(RenderWindow *app, View *view1);
    virtual ~Menu() = default;
    void draw();
    void update();

private:
    RenderWindow *m_app;
    View *m_view1;
    Event event;
    Texture texture;
    My_Sprite sprite;
    My_Text text1;
};

