/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include <iostream>
#include "Kitchen/Kitchen.hpp"
#include "Kitchen/Stock.hpp"

Kitchen::Kitchen::Kitchen(float multiplier, size_t nbCooks, long timeReplace, MsgQueue::MessageQueue msgQueue) :
_multiplier(multiplier), _nbCooks(nbCooks), _timeReplace(timeReplace),
_msgQueue(msgQueue), _maxPizza(2 * nbCooks), _saturated(false),
_time(std::chrono::system_clock::now())
{
    Singleton<CookBook>::get().setMultiplier(multiplier);
    Singleton<Stock>::get().setMultiplier(timeReplace);
    startCooking();
}

Kitchen::Kitchen::~Kitchen()
{
    stopCooking();
}

void Kitchen::Kitchen::startCooking() noexcept
{
    MsgQueue::BodyMsg request;
    // MsgQueue::Message response;

    for (size_t i = 0; i < _nbCooks; i += 1)
        _cooks.emplace_back(_toDo, _finished);

    while (CheckAfkForTooLong()) {
        _msgQueue >> request;
        // if (request.type == MsgQueue::SHELL && request.descrpt == "available") {
        //     answerReception(request, response);
        //     _msgQueue << response;
        // } else {
        //     executeRequest(request);
        // }
    }
    stopCooking();
}

void Kitchen::Kitchen::stopCooking() noexcept
{
    for (auto &thread : _cooks)
        thread.Stop();
    std::exit(0);
}

void Kitchen::Kitchen::displayStatus() const noexcept
{
    size_t i = 0;

    std::cout << std::endl << "********** KITCHEN" << "**********" << std::endl;

    std::cout << "---------- Cooks status ----------" << std::endl;
    for (const auto &it : _cooks) {
        std::cout << "\tCook n° " << i << " -> " << it.isBusy() << std::endl;
        i += 1;
    }

    Singleton<Stock>::get().displayStock();
}

bool Kitchen::Kitchen::CheckAfkForTooLong(void)
{
    bool res = false;
    _toDo.lock();
    _finished.lock();
    if (!_toDo->size() && !_finished->size()) {
        auto now = std::chrono::system_clock::now();
        auto elapsedTime = now - _time;
        if (elapsedTime < std::chrono::seconds(5))
            res = true;
    } else
        _time = std::chrono::system_clock::now();
    _finished.unlock();
    _toDo.unlock();
    return res;
}

void Kitchen::Kitchen::addOrder(Pizza::Command &pizza) noexcept
{
    _toDo.lock();
    _toDo->push_back(&pizza);
    _toDo.unlock();
}

size_t Kitchen::Kitchen::calculSaturation() noexcept
{
    size_t freeSlot = 0;

    if (_toDo->size() < _maxPizza) {
        freeSlot = _maxPizza - _toDo->size();
        _saturated = false;
    } else
        _saturated = true;
    return freeSlot;
}

void Kitchen::Kitchen::sendReadyOrder() noexcept
{
}

std::ostream &operator<<(std::ostream &out, bool isBusy)
{
    if (isBusy)
        return out << "COOKING";
    return out << "WAITING";
}