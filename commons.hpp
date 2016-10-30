#ifndef COMMONS_HPP
#define COMMONS_HPP
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

const int SCENE_NUM = 4;

#define ASSERT(expression) do \
{ \
    if(!(expression)) { \
    std::cout << "ASSERT FAILED, STOPPING " << std::endl;\
    std::cout << "At file " << __FILE__ \
    << " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << std::endl; \
    assert(expression); \
    std::exit(-1); \
    } \
} while (0)

namespace ButtonState {
//namespace for button states (for the menu)
//released is the regular state of the button, it activates when you move the mouse over it
//off means it is drawn but not clickable.
    enum basicState {released, active, pressed, off};
}

namespace GameScene {
    enum gameScene{menu,inGame,help,credits};
}

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi) {
        return v < lo ? lo : (hi < v ? hi : v);
}

#endif //COMMONS_HPP
