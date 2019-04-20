/*
** EPITECH PROJECT, 2017
** Test_criterion
** File description:
** Test de Singletons
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Kitchen/Singletons.hpp"
#include "Kitchen/CookBook.hpp"
#include "Kitchen/Stock.hpp"

TestSuite(Singleton,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: Kitchen",
.timeout = 0);

Test(Singleton, int)
{
    Singleton<int>::get();
}

Test(Singleton, CookBook)
{
    Singleton<Kitchen::CookBook>::get();
}

Test(Singleton, Stock)
{
    Singleton<Kitchen::Stock>::get();
}