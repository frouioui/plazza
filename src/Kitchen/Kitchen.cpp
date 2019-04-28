/*
** EPITECH PROJECT, 2019
** CCP_plazza_2018
** File description:
** Kitchen methods
*/

#include <iostream>
#include <cstring>
#include <sstream>
#include "Kitchen/Kitchen.hpp"
#include "Kitchen/Stock.hpp"

Kitchen::Kitchen::Kitchen(float multiplier, size_t nbCooks, long timeReplace, MsgQueue::MessageQueue &msgQueue) :
_multiplier(multiplier), _nbCooks(nbCooks), _timeReplace(timeReplace),
_msgQueue(msgQueue), _maxPizza(2 * nbCooks), _saturated(false),
_time(std::chrono::system_clock::now()), _log("Kitchen" + std::to_string(msgQueue.getId()) + ".log")
{
    Singleton<CookBook>::get().setMultiplier(multiplier);
    Singleton<Stock>::get().setMultiplier(timeReplace);
    _msgQueue.setMsgType(MsgQueue::KITCHEN);
    startCooking();
}

Kitchen::Kitchen::Kitchen(const Kitchen &old) :
_multiplier(old.getMultiplier()), _nbCooks(old.getNbCooks()), _timeReplace(old.getTimeReplace()),
_msgQueue(old.getMsgQueue()), _maxPizza(2 * old.getNbCooks()), _saturated(false),
_time(std::chrono::system_clock::now()), _log("Kitchen" + std::to_string(old.getMsgQueue().getId()) + ".log")
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
    MsgQueue::Message response = {MsgQueue::UNDEFINED, 0};
    sendImDying(response);
    _msgQueue << response;
    _log.important("I'm Stoping for beiing inactive");
    std::exit(0);
}

void Kitchen::Kitchen::startCooking() noexcept
{
    MsgQueue::BodyMsg request;
    MsgQueue::Message response;

    for (size_t i = 0; i < _nbCooks; i += 1)
        _cooks.emplace_back(_toDo, _finished);

    _log.important("Create a kitchen with " + std::to_string(_nbCooks) + " Cooks");
    while (!CheckAfkForTooLong()) {
        request.descrpt.clear();
        _msgQueue >> request;
        if (!request.descrpt.empty() && request.type == MsgQueue::SHELL &&
        request.descrpt == "available") {
            _log.info("Recpetion is asking if i can get more command");
            getFreeSlot(response);
            std::string logmsg = response.msg;
            _log.info("Sending : '" + logmsg + "'");
            _msgQueue << response;
        }
        else if (!request.descrpt.empty()) {
            executeRequest(request);
        }
        sendReadyOrder();
    }
    stopCooking();
}

void Kitchen::Kitchen::sendImDying(MsgQueue::Message &response)
{
    std::string resp = "TYPE=die\n";

    response.type = MsgQueue::RECEPTION;
    for (size_t i = 0; i < resp.size(); i++) {
        response.msg[i] = resp[i];
        response.msg[i + 1] = 0;
    }
}

static void convPizzaToMsg(MsgQueue::Message &msg, const Pizza::Command &pizza)
{
    std::string resp = "TYPE=delivery\nNAME=" + Pizza::getStringFromType(pizza._name);
    std::string size = "\nSIZE=" + Pizza::getStringFromSize(pizza._size);

    msg.type = MsgQueue::RECEPTION;
    resp += size;
    for (size_t i = 0; i < resp.size(); i++) {
        msg.msg[i] = resp[i];
        msg.msg[i + 1] = 0;
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
        response.msg[i + 1] = 0;
    }
}

void Kitchen::Kitchen::executeRequest(const MsgQueue::BodyMsg &request) noexcept
{
    switch (request.type) {
        case MsgQueue::CMD:
            _log.info("Receiving Commands");
            addOrder(request);
            break;
        case MsgQueue::SHELL:
            _log.info("Status");
            displayStatus();
            break;
        default:
            break;
    }
}

void Kitchen::Kitchen::sendReadyOrder() noexcept
{
    MsgQueue::Message msg;

    _finished.lock();
    while (!_finished->empty()) {
        Pizza::Command *pizza = _finished->front();
        _finished->pop_front();
        convPizzaToMsg(msg, *pizza);
        _log.info("Sending Finished Pizza");
        std::string logmsg = msg.msg;
        _log.info("Sending : '" + logmsg + "'");
        _msgQueue << msg;
    }
    _finished.unlock();
}

void Kitchen::Kitchen::displayStatus() const noexcept
{
    size_t i = 0;

    std::string str = "\n********** KITCHEN**********\n";

    str += "---------- Cooks status ----------\n";
    for (const auto &it : _cooks) {
        auto tmp = (it.isBusy()) ? "COOKING" : "WAITING";
        str += "\tCook n° " + std::to_string(i) + " -> " + tmp + "\n" ;
        i += 1;
    }
    str += Singleton<Stock>::get().displayStock();
    std::cout << str;
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

size_t Kitchen::Kitchen::CookisFree(void) noexcept
{
    size_t nb = 0;

    for (auto it = _cooks.begin();
    it != _cooks.end();
    it++) {
        if (!it->isBusy())
            nb += 1;
    }
    return nb;
}

bool Kitchen::Kitchen::CheckAfkForTooLong(void)
{
    bool res = false;
    _toDo.lock();
    _finished.lock();
    auto toDoSize = _toDo->size();
    auto finishSize = _finished->size();
    _toDo.unlock();
    _finished.unlock();
    if (!toDoSize && !finishSize && !this->CookisCooking()) {
        auto now = std::chrono::system_clock::now();
        auto elapsedTime = now - _time;
        if (elapsedTime > std::chrono::seconds(5))
            res = true;
    } else
        _time = std::chrono::system_clock::now();
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
    Pizza::Command *newPizza = new Pizza::Command(pizza);
    _toDo.lock();
    _toDo->push_back(newPizza);
    _toDo.unlock();
}

size_t Kitchen::Kitchen::calculSaturation() noexcept
{
    size_t freeSlot = 0;

    _toDo.lock();
    auto size = _maxPizza - _toDo->size();
    _toDo.unlock();
    size -= this->CookisFree();
    if (size < _maxPizza) {
        freeSlot = _maxPizza - size;
        _saturated = false;
    } else
        _saturated = true;
    _log.info("Check if im Satured");
    return freeSlot;
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