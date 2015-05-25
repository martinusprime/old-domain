#include "Sprite_Creator.h"

Sprite_Creator::Sprite_Creator()
{
    //ctor
}

Sprite_Creator::~Sprite_Creator()
{
    //dtor
}
void Sprite_Creator::init(RenderWindow *app_get, View *view_get)
{
    view1 = view_get;
    app = app_get;


}
void Sprite_Creator::draw()
{
    whole.draw(250, 250);
}

void Sprite_Creator::create_character( int sunlight_get)
{
    skin.init(app, "ressources/character/base_skin.png", view1);
    eyes.init(app, "ressources/character/eyes.png", view1);
    hair.init(app, "ressources/character/hair.png", view1);
    whole.init(app, "ressources/empty.png", view1);
    whole.add_sprite(&skin, sunlight_get);

    whole.add_sprite(&hair);
    whole.add_sprite(&eyes);
}
