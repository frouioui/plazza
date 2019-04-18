/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Cook
*/

#include <Kitchen/Singletons.hpp>
#include "Kitchen/CookBook.hpp"
#include "Kitchen/Cook.hpp"

Kitchen::Cook::Cook(
    SafeThread<std::list<Pizza::Command *>> &toDo,
    SafeThread<std::list<Pizza::Command *>> &finished
) :
_stop(0),
_current(nullptr),
_toDo(toDo),
_finished(finished)
{
    while (!_stop) {
        cookPizza();
    }
}

Pizza::Command Kitchen::Cook::cookPizza(void)
{
    _toDo.lock();
    auto command = _toDo->begin();
    for (; command != _toDo->end(); command++) {
        auto recipe = Singleton<Kitchen::CookBook>::get().getRecipe(**command);
        if (Singleton<Kitchen::Stock>::get().checkStockForRecipe(recipe)) {
            _current = *command;
            _toDo->erase(command);
            break;
        }
    }
    _toDo.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(Singleton<Kitchen::CookBook>::get().getCookingTime(**command)));
    return Pizza::Command{};
}

void Kitchen::Cook::Stop(void)
{
    _stop = true;
    if (_current) {
        _toDo.lock();
        _toDo->push_back(_current);
        _toDo.unlock();
    }
}

Kitchen::Cook::~Cook()
{
}
