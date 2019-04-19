/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include "Kitchen/Kitchen.hpp"

Kitchen::Kitchen::Kitchen(const int nbCooks) :
_maxPizza(2 * nbCooks)
{
    Singleton<Stock>::get().setMultiplier(nbCooks);
}

Kitchen::Kitchen::~Kitchen()
{
    std::exit(0);
}
