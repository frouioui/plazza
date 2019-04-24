/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test of the forker class
*/

#include <criterion/criterion.h>
#include "Fork.hpp"

Test(Fork, check_is_forked)
{
    Fork::Forker frk;
    pid_t pid = frk.forkProcess();

    if (pid == 0) {
        exit(1);
    } else {
        cr_assert_eq(1,1);
    }
}