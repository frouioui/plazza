/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test file of the MsgQueue IPC
*/

#include <criterion/criterion.h>
#include <iostream>
#include "MessageQueue.hpp"
#include "MessageQueueError.hpp"

using namespace MsgQueue;

Test(msg_queue_generate_key, valid_key)
{
    MessageQueue msgq("./msg_queue_test", 90);

    cr_assert_gt(msgq.generateKey(), 0);
}

Test(msg_queue_create_queue, check_creation)
{
    MessageQueue msgq("./msg_queue_test", 90);

    msgq.generateKey();
    msgq.createQueue();
}