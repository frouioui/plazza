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
    StringParse::StringParser strp("salut  t  les   \t\t \t  copains");

    strp.removeSpaceAndTabs();
    cr_assert_str_eq(strp.getStr().c_str(), "salut t les copains");
}