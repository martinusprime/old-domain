#include "Hud.h"

Hud::Hud()
{
    wood_number = 0;
    current_season = 0;
    current_year = -4000;
    year_lenght = 16;
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

//seasons icons
    season_sprite[0].init(app, "ressources/summer.png", view1);
    season_sprite[1].init(app, "ressources/autumn.png", view1);
    season_sprite[2].init(app, "ressources/winter.png", view1);
    season_sprite[3].init(app, "ressources/spring.png", view1);

    season_clock.restart();
    year_clock.restart();
    //make woodnumber int to string
    stringstream ss;
    ss << wood_number;
    string str = ss.str();
    wood_text.init(app, str.c_str(), 12, 1 );

    year_text.init(app, "-4000" , 12, 1 );
}

void Hud::draw_ressources()
{
    wood_sprite.draw( (screen_width / 2 )- 40,0 );
    wood_text.draw(screen_width / 2,0, 22 );

}

void Hud::draw()
{
    draw_ressources();

    //drawing of seasons icons and time for seasons
    season_time = season_clock.getElapsedTime();
    if(season_time.asSeconds() > year_lenght / 4)
    {
        current_season++;
        if( current_season > 3)
        {
            current_season = 0;
        }
        season_clock.restart();
    }
    season_sprite[current_season].draw( screen_width - 40, 0 );

    //displaying the year
    stringstream ss;
    ss << current_year;
    string str = ss.str();
    year_text.refill(str);

    year_time = year_clock.getElapsedTime();

    if(year_time.asSeconds() > year_lenght)
    {
        current_year++;
        if( current_season > 3)
        {
            current_season = 0;
        }
        year_clock.restart();
    }

    year_text.draw( screen_width - 110, 0 , 22);

}
