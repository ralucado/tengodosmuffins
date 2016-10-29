#ifndef MENU_H
#define MENU_H
#include "commons.hpp"
#include "scene.hpp"
#include "button.hpp"

class Menu : public Scene{
    public:
        Menu();
        Menu(const Menu& m) = delete;
        Menu(const Menu&& m) = delete;
        Menu& operator=(Menu& m) = delete;
        Menu& operator=(Menu&& m) = delete;
        void update(float deltaTime, sf::RenderWindow *window) final override;
        void draw(sf::RenderWindow *window) final override;
        void updateButtons(sf::Event e) final override;
    private:
        Button _start = Button("Resources/buttontejempl.png");
        Button _exit = Button("Resources/buttontejempl2.png");
        std::vector<Button*> _buttons;
};

#endif // MENU_H
