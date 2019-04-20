/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Header file of the string parser class
*/

#if !defined(_STRING_PARSER_HPP)
#define _STRING_PARSER_HPP

#include <string>
#include <vector>

namespace StringParse
{

    class StringParser
    {
    public:
        StringParser(const std::string &str);
        ~StringParser();

        void removeSpaceAndTabs() noexcept;
        std::vector<std::string> splitStr(char split) const noexcept;
        const std::string &getStr() const noexcept;

    private:
        std::string _str;
    };

} // StringParse


#endif // _STRING_PARSER_HPP
