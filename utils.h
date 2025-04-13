#pragma once

import std;

void replace(std::string& string, std::string oldValue, std::string newValue);
std::string getReplaced(std::string string, std::string oldValue, std::string newValue);

void removeNonAnsi(std::string& string);