/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test of the Command struct 's operator
*/

#include <criterion/criterion.h>
#include "MessageQueue.hpp"
#include "Command.hpp"

TestSuite(Command_operator,
.init = NULL,
.fini = NULL,
.signal = 0,
.exit_code = 0,
.disabled = 0,
.description = "Test the Group: Command_operator",
.timeout = 0);

Test(Command_operator, test_simple_command)
{
    Pizza::Command cmd{_name: Pizza::Regina, _size: Pizza::L};
    MsgQueue::Message msg;

    msg << cmd;
    cr_assert_str_eq(msg.msg, "TYPE=pizza\nNAME=regina\nSIZE=L");
    cr_assert_eq(msg.type, MsgQueue::UNDEFINED);
}

Test(Command_operator, send_command_to_queue)
{
    MsgQueue::MessageQueue msgq(123, "./unit_tests_plazza");
    Pizza::Command cmd{_name: Pizza::Regina, _size: Pizza::L};
    MsgQueue::Message msg;
    MsgQueue::BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msg << cmd;
    msgq << msg;
    msgq.setMsgType(MsgQueue::KITCHEN);
    msgq >> body;
    cr_assert_eq(body.type, MsgQueue::BodyType::CMD);
    cr_assert_eq(body.descrpt, "regina");
    cr_assert_eq(body.value, "L");
}