/*
** EPITECH PROJECT, 2017
** Test_criterion
** File description:
** Test de SafeThread<int>
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Kitchen/SafeThread.hpp"
#include "Kitchen/Stock.hpp"

TestSuite(SafeThread,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: SafeThread",
.timeout = 0);

Test(SafeThread, Create__G__)
{
    SafeThread<int> tmp;
}

Test(SafeThread, trylock__G__)
{
    SafeThread<Kitchen::Stock> tmp;

    cr_assert_eq(tmp.try_lock(), true);
    cr_assert_eq(tmp.try_lock(), false);
    tmp.unlock();
}

Test(SafeThread, getlock__G__, .init=cr_redirect_stdout)
{
    SafeThread<Kitchen::Stock> tmp;

    tmp.lock();
    cr_assert_no_throw(tmp->displayStock());
    tmp.unlock();
}

Test(SafeThread, getUnlock__G__)
{
    SafeThread<Kitchen::Stock> tmp;

    cr_assert_any_throw(tmp->displayStock());
}
