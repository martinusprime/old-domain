#ifndef DIALOG_H
#define DIALOG_H
#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "Sprite_Creator.h"
#include "My_Text.h"
#include "My_window.h"

class dialog
{
public:
    dialog(Grid &grid, RenderWindow *app, View *view, int screen_x, int screen_y);
    void draw();
    virtual ~dialog();
protected:
private:
    My_window m_window;
};

#endif // DIALOG_H
