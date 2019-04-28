/*
** EPITECH PROJECT, 2017
** Test_criterion
** File description:
** Test de CookBook
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Kitchen/CookBook.hpp"
#include "Kitchen/Error.hpp"
#include <iostream>

TestSuite(Kitchen_CookBook,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: Kitchen_CookBook",
.timeout = 0);

Test(Kitchen_CookBook, construct)
{
    Kitchen::CookBook();
}

Test(Kitchen_CookBook, ValueOfSubject_Margarita)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {Pizza::Margarita, Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATO"}, {"GRUYERE"}};

    cr_assert_eq(tmp.getCookingTime(command), 1);
    cr_assert_eq(recipe.size(), tmp.getRecipe(command).size());
    for (size_t i = 0; i < recipe.size(); i++) {
        cr_assert_eq(recipe.at(i).name, tmp.getRecipe(command).at(i).name);
    }
}

Test(Kitchen_CookBook, ValueOfSubject_Regina)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {Pizza::Regina, Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATO"}, {"GRUYERE"}, {"HAM"}, {"MUSHROOMS"}};

    cr_assert_eq(tmp.getCookingTime(command), 2);
    cr_assert_eq(recipe.size(), tmp.getRecipe(command).size());
    for (size_t i = 0; i < recipe.size(); i++) {
        cr_assert_eq(recipe.at(i).name, tmp.getRecipe(command).at(i).name);
    }
}

Test(Kitchen_CookBook, ValueOfSubject_Americana)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {Pizza::Americana, Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATO"}, {"GRUYERE"}, {"STEAK"}};

    cr_assert_eq(tmp.getCookingTime(command), 2);
    cr_assert_eq(recipe.size(), tmp.getRecipe(command).size());
    for (size_t i = 0; i < recipe.size(); i++) {
        cr_assert_eq(recipe.at(i).name, tmp.getRecipe(command).at(i).name);
    }
}

Test(Kitchen_CookBook, ValueOfSubject_Fantasia)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {Pizza::Fantasia, Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATO"}, {"EGGPLANT"}, {"GOAT CHEESE"}, {"CHIEF LOVE"}};

    cr_assert_eq(tmp.getCookingTime(command), 4);
    cr_assert_eq(recipe.size(), tmp.getRecipe(command).size());
    for (size_t i = 0; i < recipe.size(); i++) {
        cr_assert_eq(recipe.at(i).name, tmp.getRecipe(command).at(i).name);
    }
}

Test(Kitchen_CookBook, Value_Invalid)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {static_cast<Pizza::Type>(567), Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATO"}, {"EGGPLANT"}, {"GOAT CHEESE"}, {"CHIEF LOVE"}};

    cr_assert_throw(tmp.getCookingTime(command), Kitchen::Error);
    cr_assert_throw(tmp.getRecipe(command), Kitchen::Error);
}
