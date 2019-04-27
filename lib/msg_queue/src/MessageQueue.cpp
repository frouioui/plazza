/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the MessageQueue class
*/

#include <sys/msg.h>
#include <queue>
#include <cstring>
#include "MessageQueue.hpp"
#include "MessageQueueError.hpp"

using namespace MsgQueue;

MessageQueue::MessageQueue()
{
}

MessageQueue::MessageQueue(const int id, const std::string &path) :
    _path(path), _id(id), _msgType(RECEPTION)
{
    std::cout << id << std::endl;
}

MessageQueue::MessageQueue(const MessageQueue &msgq)
{
    std::cout << msgq._id << std::endl;
    _id = msgq._id;
    _path = msgq._path;
    _msgType = msgq._msgType;
    _msgReceive = msgq._msgReceive;
    _msgSend = msgq._msgSend;
    generateKey();
    createQueue();
}

MessageQueue::~MessageQueue()
{
}

void MessageQueue::setMsgType(MsgType type) noexcept
{
    _msgType = type;
}

MsgType MessageQueue::getMsgTypeToSend() const noexcept
{
    if (_msgType == RECEPTION)
        return KITCHEN;
    else
        return RECEPTION;
}

Message MessageQueue::getLastReceived() const noexcept
{
    return _msgReceive;
}

void MessageQueue::setMsgToSend(const Message &msg) noexcept
{
    _msgSend = msg;
}

key_t MessageQueue::generateKey(const std::string &path, const int id) const
{
    key_t key = ftok(path.c_str(), id);

    if (key == -1) {
        throw Error::DiversError{"Error with ftok", "generateKey"};
    }
    return key;
}

key_t MessageQueue::generateKey()
{
    _key = generateKey(_path, _id);
    return _key;
}

int MessageQueue::createQueue(const key_t &key) const
{
    int id = msgget(key, 0666 | IPC_CREAT);

    if (id == -1) {
        throw Error::DiversError{"Error with msgget", "createQueue"};
    }
    return id;
}

int MessageQueue::createQueue()
{
    _idQueue = createQueue(_key);
    return _idQueue;
}

int MessageQueue::sendMessage(const Message &msg, const int id) const
{
    Message *tosend = new Message(msg);
    int i = msgsnd(id, tosend, sizeof(msg.msg), IPC_NOWAIT);

    if (i == -1 && errno != ENOMSG) {
        throw Error::DiversError{"Error with msgsnd", "sendMessage"};
    }
    return 0;
}

int MessageQueue::sendMessage()
{
    sendMessage(_msgSend, _idQueue);
    return 0;
}

ssize_t MessageQueue::receiveMessage(Message &msg, const int id) const
{
    ssize_t bytes = msgrcv(id, &msg, sizeof(msg.msg), _msgType, IPC_NOWAIT);

    if ((bytes == -1 || bytes != sizeof(msg.msg)) && errno != ENOMSG) {
        throw Error::DiversError{"Error with msgrcv", "receiveMessage"};
    }
    return bytes;
}

ssize_t MessageQueue::receiveMessage()
{
    std::memset(_msgReceive.msg, 0, BUFSIZ);
    return receiveMessage(_msgReceive, _idQueue);
}

void MessageQueue::destroyQueue(const int id) const
{
    msgctl(id, IPC_RMID, NULL);
}

void MessageQueue::destroyQueue()
{
    destroyQueue(_idQueue);
}

static std::string getKey(const std::string &str, char delim)
{
    size_t delimPos = str.find(delim);

    if (delimPos == std::string::npos)
        throw Error::DiversError{"Delimiter not found", "getKey"};
    return str.substr(0, delimPos);
}

static std::string getValue(const std::string &str, char delim)
{
    size_t len = str.length();
    size_t delimPos = str.find(delim);

    if (delimPos == std::string::npos)
        throw Error::DiversError{"Delimiter not found", "getValue"};
    return str.substr(delimPos + 1, len - 1);
}

static void getType(const std::string &msgType, BodyMsg &body)
{
    if (getKey(msgType, '=') != "TYPE")
        throw Error::DiversError{"Error with type message", "getType"};
    if (getValue(msgType, '=') == "pizza")
        body.type = CMD;
    if (getValue(msgType, '=') == "error")
        body.type = ERROR;
    if (getValue(msgType, '=') == "shell")
        body.type = SHELL;
    if (getValue(msgType, '=') == "resp")
        body.type = RESP;
    if (getValue(msgType, '=') == "delivery")
        body.type = DELY;
    if (getValue(msgType, '=') == "die")
        body.type = DIE;
}

static std::queue<std::string> &parseMessage(const std::string &msg, std::queue<std::string> &msgParse)
{
    for (size_t i = 0, prev = 0; i <= msg.length(); i += 1) {
        if (i == msg.length() || msg.at(i) == '\n') {
            msgParse.push(msg.substr(prev, i - prev));
            prev = i + 1;
        }
    }
    return msgParse;
}

static void getPizza(std::queue<std::string> &msgParse, BodyMsg &body)
{
    std::string name = msgParse.front();

    if (getKey(name, '=') != "NAME")
        throw Error::DiversError{"Error with command description key", "getCommand"};
    body.descrpt = getValue(name, '=');
    msgParse.pop();
    if (msgParse.empty())
        throw Error::DiversError{"Error with command message", "getCommand"};
    if (getKey(msgParse.front(), '=') != "SIZE")
        throw Error::DiversError{"Error with command value key", "getCommand"};
    body.value = getValue(msgParse.front(), '=');
    if (body.value != "S" && body.value != "M" && body.value != "L" &&
    body.value != "XL" && body.value != "XXL")
        throw Error::DiversError{"Error with command message", "getCommand"};
}

static void getError(std::queue<std::string> &msgParse, BodyMsg &body)
{
    std::string msg = msgParse.front();

    if (getKey(msg, '=') != "MSG")
        throw Error::DiversError{"Error with error message key", "getError"};
    body.descrpt = getValue(msg, '=');
    body.value = "-1";
    msgParse.pop();
    if (!msgParse.empty())
        throw Error::DiversError{"Error with error message", "getError"};
}

static void getShell(std::queue<std::string> &msgParse, BodyMsg &body)
{
    std::string instruction = msgParse.front();

    if (getKey(instruction, '=') != "INSTRUCTION")
        throw Error::DiversError{"Error with shell description key", "getShell"};
    body.descrpt = getValue(instruction, '=');
    if (body.descrpt != "status" && body.descrpt != "available")
        throw Error::DiversError{"Error with shell description", "getShell"};
    body.value = "-1";
    msgParse.pop();
    if (!msgParse.empty())
        throw Error::DiversError{"Error with shell message", "getShell"};
}

static void getStatus(std::queue<std::string> &msgParse, BodyMsg &body)
{
    std::string name = msgParse.front();

    if (getKey(name, '=').compare("AVAILABLE") != 0)
        throw Error::DiversError{"Error with status description key", "getStatus"};
    body.descrpt = getValue(name, '=');
    if (body.descrpt != "true" && body.descrpt != "false")
        throw Error::DiversError{"Error with status description", "getStatus"};
    msgParse.pop();
    if (msgParse.empty())
        throw Error::DiversError{"Error with status message", "getStatus"};
    if (getKey(msgParse.front(), '=') != "SLOT")
        throw Error::DiversError{"Error with status value key", "getStatus"};
    body.value = getValue(msgParse.front(), '=');
}

MessageQueue &MsgQueue::operator>>(MessageQueue &msgQueue, BodyMsg &body)
{
    std::queue<std::string> msgParse;
    Message revcMsg;

    msgQueue.receiveMessage();
    revcMsg = msgQueue.getLastReceived();
    if (revcMsg.msg[0] == 0)
        return msgQueue;
    parseMessage(revcMsg.msg, msgParse);
    getType(msgParse.front(), body);
    msgParse.pop();
    switch (body.type) {
        case CMD:
            getPizza(msgParse, body);
            break;
        case DELY:
            getPizza(msgParse, body);
            break;
        case ERROR:
            getError(msgParse, body);
            break;
        case SHELL:
            getShell(msgParse, body);
            break;
        case RESP:
            getStatus(msgParse, body);
            break;
        default:
            break;
    }
    return msgQueue;
}

MessageQueue &MsgQueue::operator<<(MessageQueue &msgQueue, Message &msg)
{
    msg.type = msgQueue.getMsgTypeToSend();
    msgQueue.setMsgToSend(msg);
    msgQueue.sendMessage();
    return msgQueue;
}