#pragma once


#include <SFML/Graphics.hpp>

using namespace sf;

/* Helper class */
template<class T>
class FileLoader {
public:
    static bool loadFile(T &t, const std::string &filename);
};
