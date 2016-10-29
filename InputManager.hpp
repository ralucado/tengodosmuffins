#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP

#include <map>
#include <SFML/Window.hpp>

enum InputAction {
  shot0,
  shot1,
  recharge0,
  recharge1,
  moveX0,
  moveX1,
  MoveY0,
  moveY1
};

class InputManager {
private:
    struct helperK {
        bool b;
        sf::Keyboard::Key k;
        int c;
        bool ctrl;
        helperK(sf::Keyboard::Key k, bool ctrl) {
            this->b = false;
            this->k = k;
            this->c = 0;
            this->ctrl = ctrl;
        }
    };
    struct helperM {
        bool b;
        sf::Mouse::Button m;
        int c;
        helperM(sf::Mouse::Button m) {
            this->b = false;
            this->m = m;
            this->c = 0;
        }
    };
    struct helperJA {
        int pos;
        sf::Joystick::Axis j;
        int nPad;
        int c;
        helperJA(sf::Joystick::Axis j, int nPad) {
            this->pos = 0;
            this->j = j;
            this->nPad = nPad;
            this->c = 0;
        }
    };
    struct helperJB {
        bool b;
        int nPad;
        int nButton;
        int c;
        helperJB(int nPad, int nButton) {
            this->b = false;
            this->nPad = nPad;
            this->nButton = nButton;
            this->c = 0;
        }
    };

    static std::map<int, helperK> keyboardBinds;
    static std::map<int, helperM> mouseBinds;
    static std::map<int, helperJA> joystickAxisBinds;
    static std::map<int, helperJB> joystickButtonBinds;
    static std::pair<int, std::string> _lastTextEntered;
    static bool ctrlKeyPressed;
public:
    static void initKeyPressed();
    static void bind(InputAction s, sf::Keyboard::Key k);
    static void bindCtrl(InputAction s, sf::Keyboard::Key k);
    static void bind(InputAction s, sf::Mouse::Button m);
    static void bind(InputAction s, int nPad, sf::Joystick::Axis ja);
    static void bind(InputAction s, int nPad, int nButton);
    static bool isBinded(InputAction s);
    static bool isKeyboardBinded(InputAction s);
    static bool isMouseBinded(InputAction s);
    static bool isJoystickBinded(InputAction s);
    static float action(InputAction s);
    static float firstAction(InputAction s);
    static std::string getText();
    static bool getFirstText(std::string& firstText);
    static void update();
    static void updateEvents(sf::Event event);
};

#endif // INPUTMANAGER_HPP
