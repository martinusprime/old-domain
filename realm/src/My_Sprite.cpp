#include "My_Sprite.h"

My_Sprite::My_Sprite()
{
    //ctor
}

My_Sprite::~My_Sprite()
{
    //dtor
}
void My_Sprite::init(RenderWindow *app_get, std::string file_get, View *view_get)
{
    view1 = view_get;
    file = file_get;
    app = app_get;
    texture.loadFromFile(file.c_str());
    sprite.setTexture(texture);

    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;

}

void My_Sprite::add_sprite(string file)
{
Texture texture2;

Image background;
background.loadFromFile("ressources/tile1.png");
Image background2;
background2.loadFromFile("ressources/buildings/colonnepierre.png");

// Create a 20x20 image filled with black color
sf::Image image;
image.create(50, 50);
// Copy image1 on image2 at position (10, 10)
image.copy(background, 0, 0,  IntRect(0, 0, 50, 50));
image.copy(background2, 0, 0, IntRect(0, 0, 50, 50),true);

image.saveToFile("ressources/buildings/buildingblock.png");


    texture.loadFromFile("ressources/buildings/buildingblock.png");
    sprite.setTexture(texture);
}

string My_Sprite::get_file()
{
    return file;
}

void My_Sprite::add_sprite(My_Sprite *added_sprite)
{
    Texture texture2;

    Image background;
    background.loadFromFile(file.c_str());
    Image background2;
    background2.loadFromFile(added_sprite->get_file().c_str());

    // Create a 20x20 image filled with black color
    sf::Image image;
    image.create(50, 50);
    // Copy image1 on image2 at position (10, 10)
    image.copy(background, 0, 0,  IntRect(0, 0, 50, 50));
    image.copy(background2, 0, 0, IntRect(0, 0, 50, 50),true);

    image.saveToFile("ressources/character/character01.png");


    texture.loadFromFile("ressources/character/character01.png");
    file ="ressources/character/character01.png";
    sprite.setTexture(texture);
}

void My_Sprite::add_sprite(My_Sprite *added_sprite, int sunlight_get)
{
    int sunlight = - sunlight_get* 17;

    Texture texture2;

    Image background;
    background.loadFromFile(file.c_str());
    Image background2;
    background2.loadFromFile(added_sprite->get_file().c_str());

    sf::Image image;
    image.create(50, 50);
    // Copy image1 on image2 at position (10, 10)
    image.copy(background, 0, 0,  IntRect(0, 0, 50, 50));
    image.copy(background2, 0, 0, IntRect(0, 0, 50, 50),true);
    Color ancient_pixel;

    for(int i = 0; i< 50; i++)
    {

        for(int j = 0; j< 50; j++)
        {
            ancient_pixel = image.getPixel(i, j );
            ancient_pixel.r += sunlight  ;
            ancient_pixel.g += sunlight ;
            ancient_pixel.b += sunlight ;

            image.setPixel(i, j, ancient_pixel );
        }
    }
    image.saveToFile("ressources/character/character01.png");


    texture.loadFromFile("ressources/character/character01.png");
    file ="ressources/character/character01.png";
    sprite.setTexture(texture);
}

void My_Sprite::draw(int x_get, int y_get)
{
    x = x_get;
    y = y_get;
    sprite.setPosition(x, y);
    app->draw(sprite);
}

void My_Sprite::scale(float x_rate, float y_rate)
{
    sprite.scale(Vector2f(x_rate, y_rate));
}
void My_Sprite::set_color(int r, int g, int b, int alpha)
{
    sprite.setColor(Color(r, g, b, alpha));
}
bool My_Sprite::is_over()
{
    Vector2i a = Mouse::getPosition(*app);

    if( a.x >= x &&  a.x <= x  + w
       && a.y >= y   && a.y <= y  + h)
    {
      return true;
    }
    else return false;
}
