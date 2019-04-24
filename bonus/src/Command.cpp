/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Command
*/

#include <string>
#include "Command.hpp"

using namespace Pizza;

Type getTypeFromString(std::string &str)
{
    if (str.compare("regina") == 0)
        return Type::Regina;
    else if (str.compare("fantasia") == 0)
        return Type::Fantasia;
    else if (str.compare("margarita") == 0)
        return Type::Margarita;
    else if (str.compare("americana") == 0)
        return Type::Americana;
    else
        throw Error("Can't Find the Type");
}

bool isAType(std::string &str)
{
    return (str.compare("regina") == 0
            || str.compare("fantasia") == 0
            || str.compare("margarita") == 0
            || str.compare("americana") == 0);
}

bool isASize(std::string &str)
{
    return (str.compare("S") == 0
            || str.compare("M") == 0
            || str.compare("L") == 0
            || str.compare("XL") == 0
            || str.compare("XXL") == 0);
}

Pizza::Size getSizeFromString(std::string &str)
{
    if (str.compare("S") == 0)
        return Pizza::S;
    else if (str.compare("M") == 0)
        return Pizza::M;
    else if (str.compare("L") == 0)
        return Pizza::L;
    else if (str.compare("XL") == 0)
        return Pizza::XL;
    else if (str.compare("XXL") == 0)
        return Pizza::XXL;
    else
        throw Error("Can't Find the Size");
}
