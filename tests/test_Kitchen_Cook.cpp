/*
** EPITECH PROJECT, 2017
** Test_criterion
** File description:
** Test de Kitchen::Cook
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Kitchen/Cook.hpp"

TestSuite(Kitchen_Cook,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: Kitchen_Cook",
.timeout = 3);

Test(Kitchen_Cook, Create__G__)
{
    Pizza::Command command = {Pizza::Regina, Pizza::Size::XXL};
    SafeThread<std::list<Pizza::Command *>> _toDo;
    SafeThread<std::list<Pizza::Command *>> _finish;
    _toDo.lock();
    _toDo->push_back(&command);
    _toDo.unlock();
    Kitchen::Cook cook(_toDo, _finish);
    cook.Stop();
}

Test(Kitchen_Cook, Busy__G__, .timeout=5)
{
    Pizza::Command command = {Pizza::Fantasia, Pizza::Size::XXL};
    SafeThread<std::list<Pizza::Command *>> _toDo;
    SafeThread<std::list<Pizza::Command *>> _finish;
    _toDo.lock();
    _toDo->push_back(&command);
    _toDo->push_back(&command);
    _toDo->push_back(&command);
    _toDo.unlock();
    Kitchen::Cook cook(_toDo, _finish);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cr_expect_eq(cook.isBusy(), true);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cook.Stop();
}
