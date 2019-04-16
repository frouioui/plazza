/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ConfigReaderError class source
*/

#include <string>
#include "ConfigReaderError.hpp"

using namespace ConfigurationReader::Error;

ConfigReaderError::ConfigReaderError(const std::string &message, const std::string &where) :
    _where(where), _what(message)
{
}

const char *ConfigReaderError::ConfigReaderError::where() const noexcept
{
    return _where.c_str();
}

const char *ConfigReaderError::ConfigReaderError::what() const noexcept
{
    return _what.c_str();
}