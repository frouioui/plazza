/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Command
*/

#include <string>
#include "Command.hpp"

Pizza::Type Pizza::getTypeFromString(const std::string &str)
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

bool Pizza::isAType(std::string &str)
{
    return (str.compare("regina") == 0
            || str.compare("fantasia") == 0
            || str.compare("margarita") == 0
            || str.compare("americana") == 0);
}

bool Pizza::isASize(std::string &str)
{
    return (str.compare("S") == 0
            || str.compare("M") == 0
            || str.compare("L") == 0
            || str.compare("XL") == 0
            || str.compare("XXL") == 0);
}

Pizza::Size Pizza::getSizeFromString(const std::string &str)
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

std::string Pizza::getStringFromType(const Pizza::Type &type)
{
    switch (type) {
    case Type::Regina:
        return "regina";
    case Type::Fantasia:
        return "fantasia";
    case Type::Margarita:
        return "margarita";
    case Type::Americana:
        return "AMERICANA";
    default:
        throw Error("No Type for this Value");
        break;
    }
}

std::string Pizza::getStringFromSize(const Pizza::Size &size)
{
    switch (size) {
    case Size::S:
        return "S";
    case Size::M:
        return "M";
    case Size::L:
        return "L";
    case Size::XL:
        return "XL";
    case Size::XXL:
        return "XXL";
    default:
        throw Error("No Type for this Value");
        break;
    }
}

MsgQueue::Message &Pizza::operator<<(MsgQueue::Message &msg, const Pizza::Command &cmd)
{
    std::string pizzamsg = "TYPE=pizza\nNAME=";
    pizzamsg.append(Pizza::getStringFromType(cmd._name));
    pizzamsg.append("\nSIZE=");
    pizzamsg.append(getStringFromSize(cmd._size));
    msg.type = MsgQueue::UNDEFINED;
    for (unsigned int i = 0; i < pizzamsg.size(); i++) {
        msg.msg[i] = pizzamsg[i];
    }
    return msg;
}
