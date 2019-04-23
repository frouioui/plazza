/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the MessageQueue class
*/

#include <sys/msg.h>
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
    int i = msgsnd(id, &msg, sizeof(msg), 0);

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
    ssize_t bytes = msgrcv(id, &msg, sizeof(msg), 1, 0);

    if (bytes == -1 || bytes != sizeof(msg)) {
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