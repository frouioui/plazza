/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the Reception's error class
*/

#include "reception/Error.hpp"

using namespace ReceptionArea::Error;

ReceptionError::ReceptionError(const std::string &message, const std::string &where) :
    _where(where), _what(message)
{
}

const char *ReceptionError::ReceptionError::where() const noexcept
{
    return _where.c_str();
}

const char *ReceptionError::ReceptionError::what() const noexcept
{
    return _what.c_str();
}