#ifndef My_Text_H
#define My_Text_H
#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class My_Text
{
public:
    My_Text();
    /* copy constructor */
    My_Text(const My_Text &text_get);
    virtual ~My_Text();
    void init(RenderWindow *app_get, string content, int character_size, bool color);
    void init(RenderWindow *app_get, string content, int character_size, bool color, int color_r,  int color_g, int color_b);
    void draw(int x, int y, int character_size);
    void refill(string content);
    void change_font(string);

protected:
private:
    RenderWindow *app;
    Event event;
    Texture texture;
    Sprite sprite;
    //can not be destroyed (see sf::Text documentation)
    static Font font1;
    Text text1;
    Color current_color;
};

#endif // My_Text_H
