/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include <iostream>
#include "Kitchen/Kitchen.hpp"
#include "Kitchen/Stock.hpp"

Kitchen::Kitchen::Kitchen(size_t nbCooks) :
_nbCooks(nbCooks), _maxPizza(2 * nbCooks), _saturated(false)
{
    Singleton<Stock>::get().setMultiplier(nbCooks);
    startCooking();
}

Kitchen::Kitchen::~Kitchen()
{
    for (auto &thread : _cooks)
        thread.Stop();
    std::exit(0);
}

void Kitchen::Kitchen::startCooking() noexcept
{
    for (size_t i = 0; i < _nbCooks; i += 1)
        _cooks.emplace_back(_toDo, _finished);
}

void Kitchen::Kitchen::displayStatus() const noexcept
{
    size_t i = 0;

    // std::cout << std::endl << "********** KITCHEN N° " << getpid() << "**********" << std::endl;

    std::cout << "---------- Cooks status ----------" << std::endl;
    for (const auto &it : _cooks) {
        std::cout << "\tCook n° " << i << " -> " << it.isBusy() << std::endl; //TODO:
        i += 1;
    }

    Singleton<Stock>::get().displayStock();
}

void Kitchen::Kitchen::addOrder(Pizza::Command &pizza) noexcept
{
    _toDo.lock();
    _toDo->push_back(&pizza);
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

// std::ostream &operator<<(std::ostream &out, bool isBusy) //TODO:
// {
//     if (isBusy)
//         return out << "COOKING";
//     return out << "WAITING";
// }
