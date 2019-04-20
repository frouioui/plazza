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

Test(CookBook, Create)
{
    Singleton<Kitchen::CookBook>::get();
}