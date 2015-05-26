#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "My_Text.h"

#include "My_Sprite.h"
using namespace sf;


class Menu
{
public:
    Menu();
    virtual ~Menu();
    void draw();
    void update();
    void init(RenderWindow *app_get, View *view1_get);
protected:
private:
    RenderWindow *app;
    View *view1;
    Event event;
    Texture texture;
    My_Sprite sprite;
    My_Text text1;
};

#endif // MENU_H
