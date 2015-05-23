#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "My_Text.h"
using namespace sf;


class Menu
{
    public:
        Menu();
        virtual ~Menu();
        void draw();
        void update();
        void init(RenderWindow *app_get);
    protected:
    private:
        RenderWindow *app;
        Event event;
        Texture texture;
        Sprite sprite;
        My_Text text1;
};

#endif // MENU_H
