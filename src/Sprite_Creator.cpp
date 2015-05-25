#include "Sprite_Creator.h"

Sprite_Creator::Sprite_Creator()
{
    //ctor
}

Sprite_Creator::~Sprite_Creator()
{
    //dtor
}
void Sprite_Creator::init(RenderWindow *app_get, View *view_get, int sunlight_get)
{
    view1 = view_get;
    app = app_get;
    skin.init(app, "ressources/character/base_skin.png", view1);
    eyes.init(app, "ressources/character/eyes.png", view1);
    hair.init(app, "ressources/character/hair.png", view1);
    whole.init(app, "ressources/empty.png", view1);
    whole.add_sprite(&skin, 5);

    whole.add_sprite(&hair);
    whole.add_sprite(&eyes);

}
void Sprite_Creator::draw()
{
    whole.draw(250, 250);
}
