#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <assert.h>

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
