/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test file of the string parser library
*/

#include <criterion/criterion.h>
#include "StringParser.hpp"

Test(string_parser_removeSpaceAndTabs, simple_string_no_extra_space)
{
    StringParse::StringParser strp("salut les copains");

    strp.removeSpaceAndTabs();
    cr_assert_str_eq(strp.getStr().c_str(), "salut les copains");
}

Test(string_parser_removeSpaceAndTabs, simple_string_extra_space)
{
    StringParse::StringParser strp("salut  les  copains");

    strp.removeSpaceAndTabs();
    cr_assert_str_eq(strp.getStr().c_str(), "salut les copains");
}

Test(string_parser_removeSpaceAndTabs, complex_string_extra_space)
{
    StringParse::StringParser strp("salut  t\t  les   \t\t \t  copains ");

    strp.removeSpaceAndTabs();
    cr_assert_str_eq(strp.getStr().c_str(), "salut t les copains");
}

Test(string_parser_splitStr, simple_str)
{
    StringParse::StringParser strp("salut les copains");
    std::vector<std::string> res = strp.splitStr(' ');

    cr_assert_eq(res.size(), 3);
    cr_assert_str_eq(res[0].c_str(), "salut");
    cr_assert_str_eq(res[1].c_str(), "les");
    cr_assert_str_eq(res[2].c_str(), "copains");
}

Test(string_parser_splitStr, one_word_str)
{
    StringParse::StringParser strp("salut");
    std::vector<std::string> res = strp.splitStr(' ');

    cr_assert_eq(res.size(), 1);
    cr_assert_str_eq(res[0].c_str(), "salut");
}