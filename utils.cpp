#include "utils.h"

import std;

void replace(std::string& string, std::string oldValue, std::string newValue)
{
    while (true)
    {
        auto index = string.find(oldValue.c_str());
        if (index == std::string::npos)
        {
            break;
        }
        string.replace(index, oldValue.size(), newValue);
    }
}

std::string getReplaced(std::string string, std::string oldValue, std::string newValue)
{
    replace(string, oldValue, newValue);
    return string;
}

void removeNonAnsi(std::string& string)
{
    std::erase_if(string, [](char x) { return x < 0; });
}
