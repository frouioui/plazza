/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/
#include <cstdlib>
#include "Kitchen/Kitchen.hpp"

Kitchen::Kitchen::Kitchen(const int nbCooks) :
_maxPizza(2 * nbCooks)
{}

Kitchen::Kitchen::~Kitchen()
{
    std::exit(0);
}
