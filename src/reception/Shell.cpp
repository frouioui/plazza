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
#include "Pizza.hpp"
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
    getline(std::cin, _lastLine);
    if (_lastLine.length() == 0 || _lastLine.compare("quit") == 0) {
        _done = true;
        return QUIT;
    } else if (_lastLine.compare("help") == 0) {
        return HELPER;
    }
    return OTHER;
}

Pizza::Command Shell::Shell::parsePizza()
{
    StringParse::StringParser strp(_lastLine);
    std::vector<std::string> pizzaStrs;

    strp.removeSpaceAndTabs();
    pizzaStrs = strp.splitStr(';');
    // Go through all the entered pizzas
    for (unsigned int i = 0; i < pizzaStrs.size(); i++) {
        StringParse::StringParser pizzaParser(pizzaStrs[i]);
        std::vector<std::string> pizzaInfo;
        std::string pizzaName;
        std::string pizzaSize;
        int pizzaMultiplier;

        pizzaParser.removeSpaceAndTabs();
        pizzaInfo = pizzaParser.splitStr(' ');
        if (pizzaInfo.size() != 3) {
            // TODO: Error
        } else {
            pizzaName = pizzaInfo[0];
            pizzaSize = pizzaInfo[1];
            pizzaMultiplier = std::atoi(pizzaInfo[2].c_str());
            (void)pizzaName;
            (void)pizzaSize;
            (void)pizzaMultiplier;
            /*
            * TODO:
            * do a trivial error handling on each component
            * put them in the pizza class
            */
        }
    }
    return Pizza::Command{};
}
