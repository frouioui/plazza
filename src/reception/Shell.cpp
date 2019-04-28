/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the reception's file
*/

#include <iostream>
#include <regex>
#include "reception/Shell.hpp"
#include "reception/Error.hpp"
#include "StringParser.hpp"
#include "Command.hpp"

using namespace ReceptionArea;

Shell::Shell::Shell() : _done(false)
{
}

Shell::Shell::~Shell()
{
}

bool Shell::Shell::isDone() const noexcept
{
    return _done;
}

void Shell::Shell::writeUser(const std::string &msg) const noexcept
{
    std::cout << msg << std::endl;
}

Shell::InputType Shell::Shell::readLine() noexcept
{

    if (!getline(std::cin, _lastLine) || _lastLine.compare("quit") == 0) {
        _done = true;
        return QUIT;
    } else if (_lastLine.compare("help") == 0) {
        return HELPER;
    } else if (_lastLine.compare("status") == 0) {
        return STATUS;
    }
    return OTHER;
}

std::vector<Pizza::Command> Shell::Shell::parsePizza()
{
    std::vector<Pizza::Command> pizzas;
    StringParse::StringParser strp(_lastLine);
    std::vector<std::string> pizzaStrs;

    if (_lastLine.length() == 0) {
        return pizzas;
    }
    strp.removeSpaceAndTabs();
    pizzaStrs = strp.splitStr(';');
    for (unsigned int i = 0; i < pizzaStrs.size() && pizzaStrs[i][0] != 0; i++) {
        StringParse::StringParser pizzaParser(pizzaStrs[i]);
        std::vector<std::string> pizzaInfo;
        pizzaParser.removeSpaceAndTabs();
        pizzaInfo = pizzaParser.splitStr(' ');
        if (pizzaInfo.size() != 3) {
            throw Error::InvalidCommand("Each command must have: [NAME] [SIZE] [MULTIPLIER].", "parsePizza");
        } else {
            if (Pizza::isAType(pizzaInfo[0])
            && Pizza::isASize(pizzaInfo[1])
            && (pizzaInfo[2].size() > 1 && pizzaInfo[2][0] == 'x' && pizzaInfo[2].substr(1).find_first_not_of("1234567890") == std::string::npos)) {
                int times = std::atoi(pizzaInfo[2].substr(1).c_str());
                for (int j = 0; j < times; j++) {
                    pizzas.push_back(Pizza::Command{_name: Pizza::getTypeFromString(pizzaInfo[0]), _size: Pizza::getSizeFromString(pizzaInfo[1])});
                }
            } else {
                throw Error::InvalidCommand("The formating of your command is invalid", "parsePizza");
            }
        }
    }
    return pizzas;
}
