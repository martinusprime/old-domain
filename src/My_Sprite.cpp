#include "My_Sprite.h"

My_Sprite::My_Sprite()
{
    total_animation_time =0;
    animation_rect.height = 64;
    animation_rect.top = 0;
    animation_rect.left = 0;
    animation_rect.width = 128;
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

void My_Sprite::init(RenderWindow *app_get, std::string file_get, View *view_get, int file_number)
{
    view1 = view_get;
    app = app_get;
    int rand_limit = 3;
    srand(time(0));
    if(file_number != 0)
    {
        rand_limit = file_number;
    }

    int random = rand()% + rand_limit;
    stringstream ss;
    ss << random;
    file = file_get + ss.str() + ".png";
    cout<< file<<endl;
    ifstream file_check(file.c_str());
    while(file_check.is_open() == false && rand_limit != 1 )
    {
        rand_limit--;
        random = rand()% + rand_limit;
        ss.str("");
        ss.clear();
        ss << random;
        file = file_get +ss.str() + ".png";
        file_check.open(file.c_str());
        cout<< file<<endl;

    }
    if(file_check.is_open() == false && rand_limit == 1 )
    {
        texture.loadFromFile("ressources/empty.png");
    }
    else
    {
        texture.loadFromFile(file.c_str());
    }
    sprite.setTexture(texture);

    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
    animation_rect.height = 64;
    animation_rect.top = 0;
    animation_rect.left = 0;
    animation_rect.width = 128;
}

void My_Sprite::init(RenderWindow *app_get, string file_get, View *view_get, int animation_width_get, int animation_length_get, float total_animation_time_get)
{
    view1 = view_get;
    file = file_get;
    app = app_get;
    texture.loadFromFile(file.c_str());
    sprite.setTexture(texture);

    animation_width =animation_width_get;
    animation_length =animation_length_get;
    total_animation_time =total_animation_time_get;
    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
    animation_rect.left = 0;
    animation_rect.top = 0;
    animation_rect.width = w/animation_length;
    animation_rect.height = h;

    clock1.restart();

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

void My_Sprite::add_sprite(My_Sprite *added_sprite, string save_slot)
{
    animation_rect.height = 64;
    animation_rect.top = 0;
    animation_rect.left = 0;
    animation_rect.width = 128;

    Image background;
    background.loadFromFile(file.c_str());
    Image background2;
    background2.loadFromFile(added_sprite->get_file().c_str());

    sf::Image image;
    image.create(128, 64);

    image.copy(background, 0, 0,  IntRect(0, 0, 128, 64));
    image.copy(background2, 0, 0, IntRect(0, 0, 128, 64), true);

    image.saveToFile(save_slot);


    texture.loadFromFile(save_slot);
    file =save_slot;
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
    if(total_animation_time != 0)
    {
        time1 = clock1.getElapsedTime();
        if(time1.asSeconds() > total_animation_time / animation_length)
        {
            clock1.restart();
            animation_rect.left += animation_width;
            if(animation_rect.left >= w)
            {
                animation_rect.left = 0;
            }

        }
        sprite.setTextureRect(animation_rect);

    }

    sprite.setPosition(x, y);
    app->draw(sprite);

}
void My_Sprite::draw_tile(int x_get, int y_get, int random)
{
    x = x_get;
    y = y_get;
    animation_rect.left = 128 * random;
    animation_rect.width = 128 ;
    sprite.setTextureRect(animation_rect);
    sprite.setPosition(x, y);
    app->draw(sprite);
                //cout<<" ra "<<animation_rect.left<<endl;

}

void My_Sprite::scale(float x_rate, float y_rate)
{
    sprite.scale(Vector2f(x_rate, y_rate));
    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
}
void My_Sprite::set_color(int r, int g, int b, int alpha)
{
    //sprite.setColor(Color(r, g, b, alpha));
    // Copy image1 on image2 at position (10, 10)Texture texture2;

    Image image1;
    image1.loadFromFile(file.c_str());

    Color ancient_pixel;
    Vector2u image_size;
    image_size= image1.getSize();
    for(unsigned int i = 0; i< image_size.x; i++)
    {
        for(unsigned int j = 0; j< image_size.y; j++)
        {
            ancient_pixel = image1.getPixel(i, j );
            if(ancient_pixel != sf::Color::White)
            {
                ancient_pixel.r = r  ;
                ancient_pixel.g = g ;
                ancient_pixel.b = b ;

            }

            image1.setPixel(i, j, ancient_pixel );
        }
    }
    image1.saveToFile(file.c_str());
    texture.loadFromImage(image1);
    sprite.setTexture(texture);
}

void My_Sprite::set_color(Color color_get)
{
    //sprite.setColor(Color(r, g, b, alpha));
    // Copy image1 on image2 at position (10, 10)Texture texture2;

    Image image1;
    image1.loadFromFile(file.c_str());

    Color ancient_pixel;
    Vector2u image_size;
    image_size= image1.getSize();
    for(unsigned int i = 0; i< image_size.x; i++)
    {
        for(unsigned int j = 0; j< image_size.y; j++)
        {
            ancient_pixel = image1.getPixel(i, j );
            if(ancient_pixel != sf::Color::White)
            {
                ancient_pixel.r = color_get.r;
                ancient_pixel.g = color_get.g;
                ancient_pixel.b = color_get.b;
            }


            image1.setPixel(i, j, ancient_pixel );
        }
    }
    image1.saveToFile(file.c_str());
    texture.loadFromImage(image1);
    sprite.setTexture(texture);
}

void My_Sprite::add_color(int r, int g, int b, int alpha)
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

int My_Sprite::get_w()
{
    return w;
}

int My_Sprite::get_h()
{
    return h;
}
