/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Command related functions / methods
*/

#include "MessageQueue.hpp"
#include "Command.hpp"

MsgQueue::Message &Pizza::operator<<(MsgQueue::Message &msg, const Pizza::Command &cmd)
{
    std::string pizzamsg = "TYPE=pizza\nNAME=";

    if (cmd._name.compare("regina") == 0) {
        pizzamsg.append("regina");
    } else if (cmd._name.compare("margarita") == 0) {
        pizzamsg.append("margarita");
    } else if (cmd._name.compare("fantasia") == 0) {
        pizzamsg.append("fantasia");
    } else if (cmd._name.compare("americana") == 0) {
        pizzamsg.append("americana");
    } else {
        pizzamsg.append("error");
    }
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
    msg.type = MsgQueue::SEND;
    for (unsigned int i = 0; i < pizzamsg.size(); i++) {
        msg.msg[i] = pizzamsg[i];
    }
    return msg;
}
