/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include <iostream>
#include "Kitchen/Kitchen.hpp"
#include "Kitchen/Stock.hpp"

Kitchen::Kitchen::Kitchen(const int nbCooks) :
_maxPizza(2 * nbCooks)
{
    Singleton<Stock>::get().setMultiplier(nbCooks);
}

Kitchen::Kitchen::~Kitchen()
{
    std::exit(0);
}

void Kitchen::Kitchen::displayStatus() const noexcept
{
    Singleton<Stock>::get().displayStock();
}

void Kitchen::Kitchen::addOrder(Pizza::Command &pizza) noexcept
{
    _toDo.lock();
    _toDo->push_back(pizza);
    _toDo.unlock();
}

void Kitchen::Kitchen::calculSaturation() noexcept
{
    if (_toDo->size() < _maxPizza)
        _saturated = false;
    else
        _saturated = true;
}

bool Kitchen::Kitchen::isSaturated() const noexcept
{
    return _saturated;
}

void Kitchen::Kitchen::sendReadyOrder() noexcept
{
}

// std::ostream &operator<<(std::ostream &out, const Kitchen::Ingredient &ingredient)
// {
//     std::string name;

//     switch (ingredient) {
//         case Kitchen::Ingredient::DOE:
//             name = "Doe";
//             break;
//         case Kitchen::Ingredient::TOMATO:
//             name = "Tomato";
//             break;
//         case Kitchen::Ingredient::GRUYERE:
//             name = "Gruyere";
//             break;
//         case Kitchen::Ingredient::HAM:
//             name = "Ham";
//             break;
//         case Kitchen::Ingredient::MUSHROOMS:
//             name = "Mushrooms";
//             break;
//         case Kitchen::Ingredient::STEAK:
//             name = "Steak";
//             break;
//         case Kitchen::Ingredient::EGGPLANT:
//             name = "Eggplant";
//             break;
//         case Kitchen::Ingredient::GOATCHEESE:
//             name = "Goat cheese";
//             break;
//         case Kitchen::Ingredient::CHIEFLOVE:
//             name = "Chief love";
//             break;
//         default:
//             break;
//     }
//     return out << name;
// }