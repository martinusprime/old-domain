#ifndef SPRITE_CREATOR_H
#define SPRITE_CREATOR_H
#include "My_Sprite.h"
#include "My_window.h"


class Sprite_Creator
{
public:
    Sprite_Creator();
    void init(RenderWindow *app_get, View *view_get);
    void draw();
    void create_character( int sunlight_get);
    virtual ~Sprite_Creator();
protected:
private:
    View *view1;
    RenderWindow *app;
    My_Sprite whole, skin, hair, eyes;
    int sunlight;

};

#endif // SPRITE_CREATOR_H
