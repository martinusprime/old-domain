#include "Hud.h"

Hud::Hud()
{
    wood_number = 0;
}

Hud::~Hud()
{
    //dtor
}
void Hud::init(RenderWindow *app_get, View *view_get, int screen_width_get, int screen_height_get)
{

    view1 = view_get;
    app = app_get;
    screen_width = screen_width_get;
//initiation of resources_icones
    rock_sprite.init(app, "ressources/rock.png", view1);
    iron_sprite.init(app, "ressources/iron.png", view1);
    wood_sprite.init(app, "ressources/wood.png", view1);

    //make woodnumber int to string
    stringstream ss;
    ss << wood_number;
    string str = ss.str();
    wood_text.init(app, str.c_str(), 12, 1 );
}

void Hud::draw_ressources()
{
    wood_sprite.draw( (screen_width / 2 )- 40,0 );
    wood_text.draw(screen_width / 2,0, 22 );

}

void Hud::draw()
{
    draw_ressources();
}
