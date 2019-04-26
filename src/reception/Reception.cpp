/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the Reception class
*/

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include "reception/Reception.hpp"
#include "reception/Error.hpp"
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

void Reception::launch()
{
    ReceptionArea::Shell::InputType inputType;

    while (_shell.isDone() == false) {
        inputType = _shell.readLine();
        if (inputType == ReceptionArea::Shell::OTHER) {
            std::vector<Pizza::Command> parsePizza;
            try {
                parsePizza = _shell.parsePizza();
            } catch (Error::InvalidCommand &e) {
                std::cout << "Invalid command: " << e.what() << std::endl;
            }
            sendCommands(parsePizza);
        } else if (inputType == ReceptionArea::Shell::HELPER) {
            // TODO: Display helper in the shell
        } else if (inputType == ReceptionArea::Shell::STATUS) {
            sendStatus();
        }
        sendEmptyMsg();
    }
}

void Reception::sendEmptyMsg()
{
    MsgQueue::Message msg;
    std::string emptyMsg = "TYPE=empty\nMSG=empty";

    msg.type = MsgQueue::UNDEFINED;
    std::memset(msg.msg, 0, BUFSIZ);
    for (size_t i = 0; i < emptyMsg.size(); i += 1)
        msg.msg[i] = emptyMsg[i];
    for (unsigned int i = 0; i < _kitchens.size(); i++) {
        _kitchens[i].msgq.setMsgToSend(msg);
        _kitchens[i].msgq << msg;
    }
}

void Reception::sendStatus()
{
    MsgQueue::Message msg;

    std::strcpy(msg.msg, "TYPE=shell\nINSTRUCTION=status");
    if (_kitchens.size() == 0) {
        std::cout << "No kitchen yet." << std::endl;
        return;
    }
    for (unsigned int i = 0; i < _kitchens.size(); i++) {
        _kitchens[i].msgq.setMsgToSend(msg);
        _kitchens[i].msgq << msg;
        // _kitchens[i].msgq.sendMessage();
    }
}

void Reception::createKitchen()
{
    Fork::Forker fk;
    MsgQueue::MessageQueue msgq(rand(), "queue");
    msgq.generateKey();
    msgq.createQueue();
    pid_t pid = fk.forkProcess();

    if (pid == 0) {
        std::cout << "Start kitchen" << std::endl;
        OneKitchen kt(_multiplier, _nbCook, _replaceTime, msgq);
        exit(0);
    } else {
        ReceptionArea::KitchenManager kmn{msgq: msgq};
        _kitchens.push_back(kmn);
    }
}

void Reception::sendCommands(const std::vector<Pizza::Command> commands)
{
    MsgQueue::Message msg;

    std::strcpy(msg.msg, "TYPE=shell\nINSTRUCTION=available");
    for (unsigned int i = 0; i < commands.size(); i++) {
        bool gave = false;
        if (_kitchens.size() == 0) {
            createKitchen();
            std::cout << "Kitchen was created" << std::endl;
        }
        for (unsigned int j = 0; j < _kitchens.size() && gave == false; j++) {
            MsgQueue::BodyMsg body;

            // Ask if available
            _kitchens[j].msgq << msg;
            _kitchens[j].msgq >> body;

            // If available
            if (body.descrpt.compare("true") == 0 && body.value.compare("0") != 0) {
                MsgQueue::Message pizzaMsg;
                pizzaMsg << commands[i];
                _kitchens[j].msgq << pizzaMsg;
                gave = true;
            }
        }
        if (gave == false) {
            createKitchen();
            MsgQueue::Message pizzaMsg;
            pizzaMsg << commands[i];
            _kitchens[_kitchens.size() - 1].msgq << pizzaMsg;
        }
    }
}