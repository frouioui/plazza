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

Test(msg_queue_read_queue, check_cmd)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {SEND, "TYPE=pizza\nNAME=negrita\nSIZE=XL"};
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

Test(msg_queue_read_queue, check_error)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {SEND, "TYPE=error\nMSG=Error"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    msgq >> body;
    cr_assert_eq(body.type, BodyType::ERROR);
    cr_assert_eq(body.descrpt, "Error");
    cr_assert_eq(body.value, "-1");
    msgq.destroyQueue();
}

Test(msg_queue_read_queue, check_shell)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {SEND, "TYPE=shell\nINSTRUCTION=status"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    msgq >> body;
    cr_assert_eq(body.type, BodyType::SHELL);
    cr_assert_eq(body.descrpt, "status");
    cr_assert_eq(body.value, "-1");
    msgq.destroyQueue();
}

Test(msg_queue_read_queue, check_resp)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {SEND, "TYPE=resp\nAVAILABLE=true\nSLOT=2"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    msgq >> body;
    cr_assert_eq(body.type, BodyType::RESP);
    cr_assert_eq(body.descrpt, "true");
    cr_assert_eq(body.value, "2");
    msgq.destroyQueue();
}