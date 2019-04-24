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

Test(msg_queue_failed_read_queue, check_cmd)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {MsgQueue::RECEPTION, "TYPE=pizza\nNAME=negrita\nSIZE=R"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_str_eq(e.what(), "Error with command message");
    }
    msgq.destroyQueue();
}

Test(msg_queue_failed_read_queue, check_error)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {MsgQueue::RECEPTION, "TYPE=error\nNAME=Error"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_str_eq(e.what(), "Error with error message key");
    }
    msgq.destroyQueue();
}

Test(msg_queue_failed_read_queue, check_shell)
{
    MessageQueue msgq(90, "./msg_queue_test");
    Message msg = {MsgQueue::RECEPTION, "TYPE=shell\nINSTRUCTION=send"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_str_eq(e.what(), "Error with shell description");
    }
    msgq.destroyQueue();
}