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
    getline(std::cin, _lastLine);
    if (_lastLine.length() == 0 || _lastLine.compare("quit") == 0) {
        _done = true;
        return QUIT;
    } else if (_lastLine.compare("help") == 0) {
        return HELPER;
    } else if (_lastLine.compare("status") == 0) {
        return STATUS;
    }
    return OTHER;
}

std::vector<Pizza::Command> Shell::Shell::parsePizza() throw()
{
    std::vector<Pizza::Command> pizzas;
    StringParse::StringParser strp(_lastLine);
    std::vector<std::string> pizzaStrs;

    strp.removeSpaceAndTabs();
    pizzaStrs = strp.splitStr(';');
    for (unsigned int i = 0; i < pizzaStrs.size() && pizzaStrs[i][0] != 0; i++) {
        StringParse::StringParser pizzaParser(pizzaStrs[i]);
        std::vector<std::string> pizzaInfo;
        Pizza::Size sizePizza;
        pizzaParser.removeSpaceAndTabs();
        pizzaInfo = pizzaParser.splitStr(' ');
        if (pizzaInfo.size() != 3) {
            throw Error::InvalidCommand("Each command must have: [NAME] [SIZE] [MULTIPLIER].", "parsePizza");
        } else {
            if ((pizzaInfo[0].compare("regina") == 0 || pizzaInfo[0].compare("fantasia") == 0
            || pizzaInfo[0].compare("margarita") == 0 || pizzaInfo[0].compare("americana") == 0) &&
            (pizzaInfo[1].compare("S") == 0 || pizzaInfo[1].compare("M") == 0 || pizzaInfo[1].compare("L") == 0
            || pizzaInfo[1].compare("XL") == 0 || pizzaInfo[1].compare("XXL") == 0) &&
            (pizzaInfo[2].size() > 1 && pizzaInfo[2][0] == 'x' && pizzaInfo[2].substr(1).find_first_not_of("1234567890") == std::string::npos)) {
                if (pizzaInfo[1].compare("S") == 0)
                    sizePizza = Pizza::S;
                else if (pizzaInfo[1].compare("M") == 0)
                    sizePizza = Pizza::M;
                else if (pizzaInfo[1].compare("L") == 0)
                    sizePizza = Pizza::L;
                else if (pizzaInfo[1].compare("XL") == 0)
                    sizePizza = Pizza::XL;
                else if (pizzaInfo[1].compare("XXL") == 0)
                    sizePizza = Pizza::XXL;
                int times = std::atoi(pizzaInfo[2].substr(1).c_str());
                for (int j = 0; j < times; j++) {
                    pizzas.push_back(Pizza::Command{_name: pizzaInfo[0], _size: sizePizza});
                }
            } else {
                throw Error::InvalidCommand("The formating of your command is invalid", "parsePizza");
            }
        }
    }
    return pizzas;
}
