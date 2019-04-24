/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Command related functions / methods
*/

#include "MessageQueue.hpp"
#include "Command.hpp"

MsgQueue::Message &Pizza::operator<<(MsgQueue::Message &msg, Pizza::Command &cmd)
{
    std::string pizzamsg = "TYPE=pizza\nNAME=";

    pizzamsg.append(Pizza::getStringFromType(cmd._name));
    pizzamsg.append("\nSIZE=");
    switch (cmd._size) {
        case S:
            pizzamsg.append("S");
            break;
        case M:
            pizzamsg.append("M");
            break;
        case L:
            pizzamsg.append("L");
            break;
        case XL:
            pizzamsg.append("XL");
            break;
        case XXL:
            pizzamsg.append("XXL");
            break;
        default:
            break;
    }
    msg.type = MsgQueue::KITCHEN;
    for (unsigned int i = 0; i < pizzamsg.size(); i++) {
        msg.msg[i] = pizzamsg[i];
    }
    return msg;
}
