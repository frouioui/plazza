/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the MessageQueue class
*/

#include <sys/msg.h>
#include <queue>
#include "MessageQueue.hpp"
#include "MessageQueueError.hpp"

using namespace MsgQueue;

MessageQueue::MessageQueue()
{
}

MessageQueue::MessageQueue(const std::string &path, const int id) :
    _path(path), _id(id)
{
}

MessageQueue::~MessageQueue()
{
}

Message MessageQueue::getLastReceived() const noexcept
{
    return _msgReceive;
}

void MessageQueue::setMsgToSend(const Message &msg) noexcept
{
    if (msg.type != SEND) {
        // PROBLEM: Do we need to catch the error here?
    }
    _msgSend = msg;
}

key_t MessageQueue::generateKey(const std::string &path, const int id) const throw()
{
    key_t key = ftok(path.c_str(), id);

    if (key == -1) {
        throw Error::DiversError{"Error with ftok", "generateKey"};
    }
    return key;
}

key_t MessageQueue::generateKey() throw()
{
    _key = generateKey(_path, _id);
    return _key;
}

int MessageQueue::createQueue(const key_t &key) const throw()
{
    int id = msgget(key, 0666 | IPC_CREAT);

    if (id == -1) {
        throw Error::DiversError{"Error with msgget", "createQueue"};
    }
    return id;
}

int MessageQueue::createQueue() throw()
{
    _idQueue = createQueue(_key);
    return _idQueue;
}

int MessageQueue::sendMessage(const Message &msg, const int id) const throw()
{
    int i = msgsnd(id, &msg, sizeof(msg.msg), 0);

    if (i == -1) {
        throw Error::DiversError{"Error with msgsnd", "sendMessage"};
    }
    return 0;
}

int MessageQueue::sendMessage() throw()
{
    sendMessage(_msgSend, _idQueue);
    return 0;
}

ssize_t MessageQueue::receiveMessage(Message &msg, const int id) const throw()
{
    ssize_t bytes = msgrcv(id, &msg, sizeof(msg.msg), 0, 0);

    if (bytes == -1 || bytes != sizeof(msg.msg)) {
        throw Error::DiversError{"Error with msgrcv", "receiveMessage"};
    }
    return bytes;
}

ssize_t MessageQueue::receiveMessage() throw()
{
    return receiveMessage(_msgReceive, _idQueue);
}

void MessageQueue::destroyQueue(const int id) const throw()
{
    msgctl(id, IPC_RMID, NULL);
}

void MessageQueue::destroyQueue() throw()
{
    destroyQueue(_idQueue);
}

static std::string getKey(const std::string &str, char delim) throw()
{
    size_t delimPos = str.find(delim);

    if (delimPos == std::string::npos)
        throw Error::DiversError{"Delimiter not found", "getKey"};
    return str.substr(0, delimPos);
}

static std::string getValue(const std::string &str, char delim) throw()
{
    size_t len = str.length();
    size_t delimPos = str.find(delim);

    if (delimPos == std::string::npos)
        throw Error::DiversError{"Delimiter not found", "getValue"};
    return str.substr(delimPos + 1, len - 1);
}

static void getType(const std::string &msgType, BodyMsg &body) throw()
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

static void getCommand(std::queue<std::string> &msgParse, BodyMsg &body) throw()
{
    std::string name = msgParse.front();

    if (getKey(name, '=') != "NAME")
        throw Error::DiversError{"Error with command message", "getCommand"};
    body.descrpt = getValue(name, '=');
    msgParse.pop();
    if (msgParse.empty())
        throw Error::DiversError{"Error with command message", "getCommand"};
    body.value = getValue(msgParse.front(), '=');
    if (body.value != "S" && body.value != "M" && body.value != "L" &&
    body.value != "XL" && body.value != "XXL")
        throw Error::DiversError{"Error with command message", "getCommand"};
}

static void getError(std::queue<std::string> &msgParse, BodyMsg &body) throw()
{
    std::string msg = msgParse.front();

    if (getKey(msg, '=') != "MSG")
        throw Error::DiversError{"Error with error message", "getError"};
    body.descrpt = getValue(msg, '=');
    body.value = -1;
    msgParse.pop();
    if (!msgParse.empty())
        throw Error::DiversError{"Error with error message", "getError"};
}

static void getShell(std::queue<std::string> &msgParse, BodyMsg &body) throw()
{
    std::string instruction = msgParse.front();

    if (getKey(instruction, '=') != "INSTRUCTION")
        throw Error::DiversError{"Error with shell message", "getShell"};
    body.descrpt = getValue(instruction, '=');
    body.value = -1;
    msgParse.pop();
    if (!msgParse.empty())
        throw Error::DiversError{"Error with shell message", "getShell"};
}

static void getStatus(std::queue<std::string> &msgParse, BodyMsg &body) throw()
{
    std::string name = msgParse.front();

    if (getKey(name, '=') != "AVAILABLE")
        throw Error::DiversError{"Error with status message", "getStatus"};
    body.descrpt = getValue(name, '=');
    msgParse.pop();
    if (msgParse.empty())
        throw Error::DiversError{"Error with status message", "getStatus"};
    body.value = getValue(msgParse.front(), '=');
    if (body.value != "true" && body.value != "false")
        throw Error::DiversError{"Error with status message", "getStatus"};
}

MessageQueue &MsgQueue::operator>>(MessageQueue &msgQueue, BodyMsg &body)
{
    std::queue<std::string> msgParse;
    Message revcMsg;

    msgQueue.receiveMessage();
    revcMsg = msgQueue.getLastReceived();
    parseMessage(revcMsg.msg, msgParse);
    getType(msgParse.front(), body);
    msgParse.pop();
    switch (body.type) {
        case CMD:
            getCommand(msgParse, body);
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
    msgQueue.setMsgToSend(msg);
    msgQueue.sendMessage();
    return msgQueue;
}