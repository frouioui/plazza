/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the string parser class
*/

#include "StringParser.hpp"

using namespace StringParse;

StringParser::StringParser(const std::string &str) : _str(str)
{
}

StringParser::~StringParser()
{
}

const std::string &StringParser::getStr() const noexcept
{
    return _str;
}

std::vector<std::string> StringParser::splitStr(char split) const noexcept
{
    std::vector<std::string> res;
    size_t oldPos = 0;
    size_t pos = 0;

    pos = _str.find_first_of(split);
    if (pos == std::string::npos) {
        res.push_back(_str);
    } else {
        res.push_back(_str.substr(0, pos));
        oldPos = pos;
    }
    while (pos != std::string::npos) {
        pos = _str.find_first_of(split, oldPos + 1);
        if (pos == std::string::npos) {
            res.push_back(_str.substr(oldPos + 1));
        } else {
            res.push_back(_str.substr(oldPos + 1, pos - oldPos - 1));
            oldPos = pos;
        }
    }
    return (res);
}

void StringParser::removeSpaceAndTabs() noexcept
{
    unsigned int j = 0;

    for (unsigned int i = 0; i < _str.size(); i++) {
        if ((_str[i] == ' ' || _str[i] == '\t') && (_str[i + 1] == ' ' || _str[i + 1] == '\t')) {
            i++;
            while (_str[i] == ' ' || _str[i] == '\t') {
                for (j = i; j + 1 < _str.size(); j++) {
                    _str[j] = _str[j + 1];
                }
                _str[_str.size() - 1] = '\0';
            }
        }
    }
}