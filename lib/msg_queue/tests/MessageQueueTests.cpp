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
    MessageQueue msgq(90, "./msg_queue_test");

    cr_assert_gt(msgq.generateKey(), 0);
}

Test(msg_queue_create_queue, check_creation)
{
    MessageQueue msgq(90, "./msg_queue_test");

    msgq.generateKey();
    msgq.createQueue();
    msgq.destroyQueue();
}

Test(msg_queue_create_queue, check_send)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {RECEPTION, "TYPE=pizza\nNAME=negrita\nSIZE=XL"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    msgq >> body;
    cr_assert_eq(body.type, BodyType::CMD);
    cr_assert_eq(body.descrpt, "negrita");
    cr_assert_eq(body.value, "XL");
    msgq.destroyQueue();
}

Test(msg_queue_create_queue, check_receive)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {RECEPTION, "TYPE=pizza\nNAME=negrita\nSIZE=XL"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq << msg;
    msgq >> body;
    cr_assert_eq(body.type, BodyType::CMD);
    cr_assert_eq(body.descrpt, "negrita");
    cr_assert_eq(body.value, "XL");
    msgq.destroyQueue();
}