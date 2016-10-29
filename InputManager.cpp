#include "InputManager.hpp"

std::map<int, InputManager::helperK> InputManager::keyboardBinds;
std::map<int, InputManager::helperM> InputManager::mouseBinds;
std::map<int, InputManager::helperJA> InputManager::joystickAxisBinds;
std::map<int, InputManager::helperJB> InputManager::joystickButtonBinds;

std::pair<int, std::string> InputManager::_lastTextEntered;

bool InputManager::ctrlKeyPressed = false;

// std::vector< InputManager::helperK> InputManager::keysPressed;

// void InputManager::

void InputManager::bind(InputAction s, sf::Keyboard::Key k) {
    if (keyboardBinds.find(s) == keyboardBinds.end()) keyboardBinds.insert(std::make_pair(s,helperK(k,false)));
    else keyboardBinds.at(s) = helperK(k,false);
}

void InputManager::bindCtrl(InputAction s, sf::Keyboard::Key k) {
    if (keyboardBinds.find(s) == keyboardBinds.end()) keyboardBinds.insert(std::make_pair(s,helperK(k,true)));
    else keyboardBinds.at(s) = helperK(k,true);
}

void InputManager::bind(InputAction s, sf::Mouse::Button m) {
    if (mouseBinds.find(s) == mouseBinds.end()) mouseBinds.insert(std::make_pair(s,helperM(m)));
    else mouseBinds.at(s) = helperM(m);
}

void InputManager::bind(InputAction s, int nPad, sf::Joystick::Axis ja) {
    if (joystickAxisBinds.find(s) == joystickAxisBinds.end()) joystickAxisBinds.insert(std::make_pair(s,helperJA(ja,nPad)));
    else joystickAxisBinds.at(s) = helperJA(ja, nPad);
}

void InputManager::bind(InputAction s, int nPad, int nButton) {
    if (joystickButtonBinds.find(s) == joystickButtonBinds.end()) joystickButtonBinds.insert(std::make_pair(s,helperJB(nPad,nButton)));
    else joystickButtonBinds.at(s) = helperJB(nPad,nButton);
}

bool InputManager::isBinded(InputAction s) {
    return (keyboardBinds.find(s) != keyboardBinds.end())
            || (mouseBinds.find(s) != mouseBinds.end()
            || joystickAxisBinds.find(s) != joystickAxisBinds.end()
            || joystickButtonBinds.find(s) != joystickButtonBinds.end());
}

bool InputManager::isKeyboardBinded(InputAction s) {
    return (keyboardBinds.find(s) != keyboardBinds.end());
}

bool InputManager::isMouseBinded(InputAction s) {
    return (mouseBinds.find(s) != mouseBinds.end());
}

bool InputManager::isJoystickBinded(InputAction s) {
    return (joystickAxisBinds.find(s) != joystickAxisBinds.end() || joystickButtonBinds.find(s) != joystickButtonBinds.end());
}

float InputManager::action(InputAction s) {
    auto itK = keyboardBinds.find(s);
    if (itK != keyboardBinds.end() && (*itK).second.b && ( (!(*itK).second.ctrl && !ctrlKeyPressed) || ((*itK).second.ctrl && ctrlKeyPressed) ) ) return true;
    else {
        auto itM = mouseBinds.find(s);
        if (itM != mouseBinds.end() && (*itM).second.b) return true;
        else {
            auto itJA = joystickAxisBinds.find(s);
            if (itJA != joystickAxisBinds.end() && (*itJA).second.pos) return (*itJA).second.pos/100.f;
            else {
                auto itJB = joystickButtonBinds.find(s);
                if (itJB != joystickButtonBinds.end()) return (*itJB).second.b;
                else return false;
            }
        }
    }
}

float InputManager::firstAction(InputAction s) {
    auto itK = keyboardBinds.find(s);
    if (itK != keyboardBinds.end() && (*itK).second.b && (*itK).second.c == 1 && ( (!(*itK).second.ctrl && !ctrlKeyPressed) || ((*itK).second.ctrl && ctrlKeyPressed) ) ) {
        // (*itK).second.c += 1;
        return true;
    }
    else {
        auto itM = mouseBinds.find(s);
        if (itM != mouseBinds.end() && (*itM).second.b && (*itM).second.c == 1) {
            // (*itM).second.c += 1;
            return true;
        }
        else {
            auto itJA = joystickAxisBinds.find(s);
            if (itJA != joystickAxisBinds.end() && (*itJA).second.pos && (*itJA).second.c == 1) {
                // (*itJA).second.c += 1;
                return (*itJA).second.pos/100.f;
            }
            else {
                auto itJB = joystickButtonBinds.find(s);
                if (itJB != joystickButtonBinds.end() && (*itJB).second.c == 1) {
                    // (*itJB).second.c += 1;
                    return (*itJB).second.b;
                }
                else return false;
            }
        }
    }
}

std::string InputManager::getText() {
    return _lastTextEntered.second;
}

bool InputManager::getFirstText(std::string& firstText) {
    if (_lastTextEntered.first == 0) {
        firstText = _lastTextEntered.second;
        _lastTextEntered.first += 1;
        return true;
    }
    else return false;
}

void InputManager::update() {
    for (auto& kb : keyboardBinds) {
        if (sf::Keyboard::isKeyPressed(kb.second.k)) {
            kb.second.b = true;
            kb.second.c += 1;
        }
        else {
            kb.second.b = false;
            kb.second.c = 0;
        }
    }
    for (auto& ms : mouseBinds) {
        if (sf::Mouse::isButtonPressed(ms.second.m)) {
            ms.second.b = true;
            ms.second.c += 1;
        }
        else {
            ms.second.b = false;
            ms.second.c = 0;
        }
    }
    for (auto& jas : joystickAxisBinds) {
        if (sf::Joystick::getAxisPosition(jas.second.nPad,jas.second.j)) {
            jas.second.pos = true;
            jas.second.c += 1;
        }
        else {
            jas.second.pos = false;
            jas.second.c = 0;
        }

    }
    for (auto& jbs : joystickButtonBinds) {
        if (sf::Joystick::isButtonPressed(jbs.second.nPad,jbs.second.nButton)) {
            jbs.second.b = true;
            jbs.second.c += 1;
        }
        else {
            jbs.second.b = false;
            jbs.second.c = 0;
        }
    }
    ctrlKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RControl);
    _lastTextEntered.first += 1;
}

void InputManager::updateEvents(sf::Event event) {
    if (event.type == sf::Event::TextEntered) {
      char c = event.text.unicode;
      if (!isprint(c)) return;
      if (_lastTextEntered.first == -1) _lastTextEntered.second += c;
      else _lastTextEntered = std::make_pair(-1,static_cast<char>(c));
    }
    else if (event.type == sf::Event::KeyPressed) {
      for (auto& kb : keyboardBinds) {
        if (kb.second.k == event.key.code) {
          kb.second.b = true;
          kb.second.c = 0;
          break;
        }
      }
    }
}
