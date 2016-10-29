#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "commons.hpp"
class Button : public sf::Sprite{

public:
    Button(std::string path);
    //upon creating a button, its state is set to off by default, you must activate it maually after declaration
    //Button();
    void turnOn();
    void turnOff();
    bool isOn();
    int getClicks();
    //buttons auto-detect if they are pressed, you just have to pass a mouse-event to them
    void handleMouseEvent(sf::Event& event);
    void update(sf::Vector2i mousePosition);

protected:
    int _xSize;
    int _ySize;
    sf::Texture _texture;
    bool inside(sf::Vector2i position);

private:
    int _clicks;
    int _state;

    void initTexture(std::string path);
};

#endif // BUTTON_HPP
