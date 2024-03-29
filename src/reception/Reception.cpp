/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the Reception class
*/

#include <vector>
#include <cstring>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <iostream>
#include "reception/Reception.hpp"
#include "reception/Error.hpp"
#include "Logger.hpp"
#include "Fork.hpp"
#include "StringParser.hpp"

using namespace ReceptionArea;

Reception::Reception()
{
    srand(time(NULL));
}

Reception::~Reception()
{
}

void Reception::setValues(const int argc, const char *argv[])
{
    std::string shelp = "-h";
    std::string lhelp = "--help";

    if (argc == 2 && (shelp.compare(argv[1]) == 0 || lhelp.compare(argv[1]) == 0)) {
        throw Error::Helper("Display helper", "setValues");
    } else if (argc != 4) {
        throw Error::InvalidArgument("Invalid argument, need at least 4 arguments.", "setValues");
    }
    std::string coefstr(argv[1]);
    std::string cookstr(argv[2]);
    std::string timestr(argv[3]);

    if (coefstr.find_first_not_of(".0123456789") != std::string::npos ||
        cookstr.find_first_not_of("0123456789") != std::string::npos ||
        timestr.find_first_not_of("0123456789") != std::string::npos ) {
        throw Error::InvalidArgument("Argument must be positiv float value or integers.", "setValues");
    }
    if (coefstr.find_first_of(".") != std::string::npos) {
        _multiplier = std::atof(coefstr.c_str());
        if (!(_multiplier > 0 && _multiplier < 1)) {
            throw Error::InvalidArgument("The multiplier should be between 0.00 and 1.00.", "setValues");
        }
    } else {
        _multiplier = (float)std::atoi(coefstr.c_str());
    }
    _nbCook = std::atoi(cookstr.c_str());
    _replaceTime = std::atol(timestr.c_str());
}

void Reception::checkKitchens()
{
    for (unsigned int i = 0; i < _kitchens.size(); i++) {
        MsgQueue::BodyMsg body;
        bool wait = false;

        body.type = MsgQueue::NONE;
        while (body.type == MsgQueue::DELY || body.type == MsgQueue::DIE || wait == false) {
            wait = true;
            _kitchens[i].msgq >> body;
            if (body.type == MsgQueue::DELY) {
                _logger.info("Pizza done, pizza: " + body.descrpt + " size: " + body.value);
            } else if (body.type == MsgQueue::DIE) {
                _logger.info("Kitchen is now closed id = " + std::to_string(_kitchens[i].msgq.getId()));
                _kitchens.erase(_kitchens.begin() + i);
                body.type = MsgQueue::NONE;
            }
        }
    }
}

void Reception::launch()
{
    ReceptionArea::Shell::InputType inputType;

    while (_shell.isDone() == false) {
        std::cout << "$> ";
        inputType = _shell.readLine();
        if (_shell.isDone())
            break;
        checkKitchens();
        if (inputType == ReceptionArea::Shell::OTHER) {
            std::vector<Pizza::Command> parsePizza;
            try {
                parsePizza = _shell.parsePizza();
            } catch (Error::InvalidCommand &e) {
                _logger.important("Invalid command: " + std::string(e.what()));
                continue;
            }
            if (parsePizza.size() > 0)
                sendCommands(parsePizza);
        } else if (inputType == ReceptionArea::Shell::HELPER) {
            std::cout << "Helpler" << std::endl;
        } else if (inputType == ReceptionArea::Shell::STATUS) {
            sendStatus();
        }
    }
}

void Reception::sendStatus()
{
    MsgQueue::Message msg;

    memset(msg.msg, 0, 128);
    std::strcpy(msg.msg, "TYPE=shell\nINSTRUCTION=status");
    if (_kitchens.size() == 0) {
        _logger.info("No kitchen yet");
        return;
    }
    for (unsigned int i = 0; i < _kitchens.size(); i++) {
        _kitchens[i].msgq.setMsgToSend(msg);
        _kitchens[i].msgq << msg;
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int Reception::createKitchen()
{
    Fork::Forker fk;
    MsgQueue::MessageQueue msgq(rand(), "queue");
    msgq.generateKey();
    msgq.createQueue();
    pid_t pid = fk.forkProcess();

    if (pid == 0) {
        _logger.info("Starting a new kitchen");
        OneKitchen kt(_multiplier, _nbCook, _replaceTime, msgq);
        exit(0);
    } else if (pid > 0) {
        ReceptionArea::KitchenManager kmn{msgq: msgq};
        _kitchens.push_back(kmn);
    } else {
        _logger.important("Order was canceled. You hardware is about to die ... Try again in a few seconds.");
        return 1;
    }
    return 0;
}

void Reception::sendCommands(const std::vector<Pizza::Command> commands)
{
    MsgQueue::Message msg;

    memset(msg.msg, 0, 128);
    std::strcpy(msg.msg, "TYPE=shell\nINSTRUCTION=available");
    if (commands.size() > 100) {
        _logger.important("One client can't order as many pizza ... You are too greedy.");
        return;
    }
    for (unsigned int i = 0; i < commands.size(); i++) {
        bool gave = false;
        if (_kitchens.size() == 0) {
            if (createKitchen())
                return;
        }
        for (unsigned int j = 0; j < _kitchens.size() && gave == false; j++) {
            MsgQueue::BodyMsg body = {MsgQueue::NONE, "", ""};
            _kitchens[j].msgq << msg;
            while (body.type != MsgQueue::RESP) {
                _kitchens[j].msgq >> body;
            }
            int slots = std::atoi(body.value.c_str());
            if (body.descrpt.compare("true") == 0 && slots > 0) {
                _logger.info("Sending order to kitchen");
                MsgQueue::Message pizzaMsg;
                pizzaMsg << commands[i];
                _kitchens[j].msgq << pizzaMsg;
                gave = true;
            }
        }
        if (gave == false) {
            _logger.info("No kitchen available");
            createKitchen();
            MsgQueue::Message pizzaMsg;
            _logger.info("Sending order to the new kitchen");
            pizzaMsg << commands[i];
            _kitchens[_kitchens.size() - 1].msgq << pizzaMsg;
        }
    }
}