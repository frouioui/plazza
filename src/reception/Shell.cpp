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

Pizza::Pizza Shell::Shell::parsePizza()
{

    return Pizza::Pizza{};
}
