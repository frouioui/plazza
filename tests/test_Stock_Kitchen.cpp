/*
** EPITECH PROJECT, 2017
** Test_criterion
** File description:
** Test de Kitchen::Stock
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <thread>
#include <iostream>
#include "Kitchen/Stock.hpp"

TestSuite(Kitchen_Stock,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: Kitchen_Stock",
.timeout = 0);

Test(Kitchen_Stock, Create__G__)
{
    Kitchen::Stock tmp;
    tmp.setMultiplier(01);
}

Test(Kitchen_Stock, Recipe__G__, .timeout=1)
{
    Kitchen::Stock tmp;
    Kitchen::CookBook::Recipe recipe = {{"DOE"}};

    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), false);
}

Test(Kitchen_Stock, Display__G__, .init=cr_redirect_stdout)
{
    Kitchen::Stock tmp;

    tmp.displayStock();
    std::cout.flush();
    cr_assert_stdout_eq_str("------ Stock of ingredients ------\n\
\tCHIEF LOVE: 5\n\
\tDOE: 5\n\
\tEGGPLANT: 5\n\
\tGOAT CHEESE: 5\n\
\tGRUYERE: 5\n\
\tHAM: 5\n\
\tMUSHROOMS: 5\n\
\tSTEAK: 5\n\
\tTOMATO: 5\n");
}

Test(Kitchen_Stock, Refill__G__)
{
    Kitchen::Stock tmp;
    Kitchen::CookBook::Recipe recipe = {{"DOE"}};

    tmp.setMultiplier(1);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), true);
    cr_assert_eq(tmp.getRecipe(recipe), false);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    cr_assert_eq(tmp.getRecipe(recipe), true);
}