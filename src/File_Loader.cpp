
#include <iostream>

#include "File_Loader.h"

namespace
{
    void printError(const std::string &filename)
    {
        std::cerr << "loadFromFile failed! File name: " << filename << "\n";
    }
}

template <class T> bool FileLoader<T>::loadFile(T &t, const std::string &filename)
{
    bool ret = t.loadFromFile(filename);
    if (!ret) {
        printError(filename);
    }
    return ret;
}

// Explicit template instantiation
template class FileLoader<sf::Texture>;
template class FileLoader<sf::Font>;
template class FileLoader<sf::Image>;