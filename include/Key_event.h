#ifndef KEY_EVENT_H
#define KEY_EVENT_H

#include <SFML/Graphics.hpp>
#include <map>

enum Action {
    ACT_ZOOM_IN,
    ACT_ZOOM_OUT,
    ACT_GO_UP,
    ACT_GO_DOWN,
    ACT_GO_RIGHT,
    ACT_GO_LEFT,
    ACT_CLOSE_APP
};

class Key_event_handler
{
public:
    Key_event_handler();
    virtual ~Key_event_handler();
    /* return true if an event was handled
       action is an "out" parameter. */
    bool manage_key_event(const sf::Event &event, const sf::RenderWindow *app, Action &action, sf::Vector2i &mouse_vec);
protected:
private:
    std::map<sf::Keyboard::Key, Action> key_action;
};

#endif // KEY_EVENT_H
