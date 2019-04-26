/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include <iostream>
#include <cstring>
#include "Kitchen/Kitchen.hpp"
#include "Kitchen/Stock.hpp"

Kitchen::Kitchen::Kitchen(float multiplier, size_t nbCooks, long timeReplace, MsgQueue::MessageQueue &msgQueue) :
_multiplier(multiplier), _nbCooks(nbCooks), _timeReplace(timeReplace),
_msgQueue(msgQueue), _maxPizza(2 * nbCooks), _saturated(false),
_time(std::chrono::system_clock::now())
{
    Singleton<CookBook>::get().setMultiplier(multiplier);
    Singleton<Stock>::get().setMultiplier(timeReplace);
    _msgQueue.setMsgType(MsgQueue::KITCHEN);
    startCooking();
}

Kitchen::Kitchen::Kitchen(const Kitchen &old) :
_multiplier(old.getMultiplier()), _nbCooks(old.getNbCooks()), _timeReplace(old.getTimeReplace()),
_msgQueue(old.getMsgQueue()), _maxPizza(2 * old.getNbCooks()), _saturated(false),
_time(std::chrono::system_clock::now())
{
    Singleton<CookBook>::get().setMultiplier(old.getMultiplier());
    Singleton<Stock>::get().setMultiplier(old.getTimeReplace());
    _msgQueue.setMsgType(MsgQueue::KITCHEN);
    startCooking();
}

Kitchen::Kitchen::~Kitchen()
{
    stopCooking();
}

void Kitchen::Kitchen::stopCooking() noexcept
{
    for (auto &thread : _cooks)
        thread.Stop();
    std::exit(0);
}

void Kitchen::Kitchen::startCooking() noexcept
{
    MsgQueue::BodyMsg request;
    MsgQueue::Message response;

    for (size_t i = 0; i < _nbCooks; i += 1)
        _cooks.emplace_back(_toDo, _finished);

    // while (CheckAfkForTooLong()) {
    while (true) {
        request.descrpt.clear();
        _msgQueue >> request;
        if (!request.descrpt.empty() && request.type == MsgQueue::SHELL &&
        request.descrpt == "available") {
            getFreeSlot(response);
            _msgQueue << response;
        }
        else if (!request.descrpt.empty()) {
            executeRequest(request);
        }
        sendReadyOrder();
    }
    // stopCooking();
}

static void convPizzaToMsg(MsgQueue::Message &msg, const Pizza::Command &pizza)
{
    std::string resp = "TYPE=delivery\nNAME=" + Pizza::getStringFromType(pizza._name);
    std::string size = "\nSIZE=" + Pizza::getStringFromSize(pizza._size);

    msg.type = MsgQueue::RECEPTION;
    resp += size;
    for (size_t i = 0; i < resp.size(); i++) {
        msg.msg[i] = resp[i];
    }
}

void Kitchen::Kitchen::getFreeSlot(MsgQueue::Message &response)
{
    std::string resp = "TYPE=resp\nAVAILABLE=";
    std::string slot = "\nSLOT=" + std::to_string(calculSaturation());

    response.type = MsgQueue::RECEPTION;
    if (_saturated == true)
        resp += "false";
    else
        resp += "true";
    resp += slot;
    for (size_t i = 0; i < resp.size(); i++) {
        response.msg[i] = resp[i];
    }
}

void Kitchen::Kitchen::executeRequest(const MsgQueue::BodyMsg &request) noexcept
{
    switch (request.type) {
        case MsgQueue::CMD:
            addOrder(request);
            break;
        case MsgQueue::SHELL:
            displayStatus();
            break;
        default:
            break;
    }
}

void Kitchen::Kitchen::sendReadyOrder() noexcept
{
    MsgQueue::Message msg;

    while (!_finished->empty()) {
        Pizza::Command *pizza = _finished->front();
        _finished->pop_front();
        convPizzaToMsg(msg, *pizza);
        _msgQueue << msg;
    }
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

bool Kitchen::Kitchen::CookisCooking(void) noexcept
{
    for (auto it = _cooks.begin();
    it != _cooks.end();
    it++) {
        if (it->isBusy())
            return true;
    }
    return false;
}

bool Kitchen::Kitchen::CheckAfkForTooLong(void)
{
    bool res = false;
    _toDo.lock();
    _finished.lock();
    if (!_toDo->size() && !_finished->size() && !this->CookisCooking()) {
        auto now = std::chrono::system_clock::now();
        auto elapsedTime = now - _time;
        if (elapsedTime < std::chrono::seconds(5))
            res = true;
    } else
        _time = std::chrono::system_clock::now();
    _toDo.unlock();
    _finished.unlock();
    return res;
}

static Pizza::Command convMsgToPizza(const MsgQueue::BodyMsg &msg)
{
    Pizza::Type name = Pizza::getTypeFromString(msg.descrpt);
    Pizza::Size size = Pizza::getSizeFromString(msg.value);
    Pizza::Command pizza = {name, size};

    return pizza;
}

void Kitchen::Kitchen::addOrder(const MsgQueue::BodyMsg &msg) noexcept
{
    Pizza::Command pizza = convMsgToPizza(msg);

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

std::ostream &operator<<(std::ostream &out, bool isBusy)
{
    if (isBusy)
        return out << "COOKING";
    return out << "WAITING";
}

float Kitchen::Kitchen::getMultiplier() const
{
    return _multiplier;
}

size_t Kitchen::Kitchen::getNbCooks() const
{
    return _nbCooks;
}

long Kitchen::Kitchen::getTimeReplace() const
{
    return _timeReplace;
}

const MsgQueue::MessageQueue &Kitchen::Kitchen::getMsgQueue() const
{
    return _msgQueue;
}