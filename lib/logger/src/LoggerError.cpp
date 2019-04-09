/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ConfigReaderError class source
*/

#include <string>
#include "LoggerError.hpp"

using namespace Log::Error;

LoggerError::LoggerError(const std::string &message, const std::string &where) :
    _where(where), _what(message)
{
}

const char *LoggerError::where() const noexcept
{
    return _where.c_str();
}

const char *LoggerError::what() const noexcept
{
    return _what.c_str();
}