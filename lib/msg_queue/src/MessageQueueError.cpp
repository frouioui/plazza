/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Message queue error
*/

#include <string>
#include "MessageQueueError.hpp"

using namespace MsgQueue::Error;

MsgQueueError::MsgQueueError(const std::string &message, const std::string &where) :
    _where(where), _what(message)
{
}

const char *MsgQueueError::where() const noexcept
{
    return _where.c_str();
}

const char *MsgQueueError::what() const noexcept
{
    return _what.c_str();
}