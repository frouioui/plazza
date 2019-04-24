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
    MessageQueue msgq("./msg_queue_test", 90);
    Message msg = {SEND, "TYPE=pizza\nNAME=negrita\nSIZE=R"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_eq(e.what(), "Error with command message");
    }
}

Test(msg_queue_failed_read_queue, check_error)
{
    MessageQueue msgq("./msg_queue_test", 90);
    Message msg = {SEND, "TYPE=error\nNAME=Error"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_eq(e.what(), "Error with error message key");
    }
}

Test(msg_queue_failed_read_queue, check_shell)
{
    MessageQueue msgq("./msg_queue_test", 90);
    Message msg = {SEND, "TYPE=shell\nINSTRUCTION=send"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_eq(e.what(), "Error with status description");
    }
}

Test(msg_queue_failed_read_queue, check_resp)
{
    MessageQueue msgq("./msg_queue_test", 90);
    Message msg = {SEND, "TYPE=resp\nAVAILABLE=ready\nSLOT=2"};
    BodyMsg body;

    msgq.generateKey();
    msgq.createQueue();
    msgq.setMsgToSend(msg);
    msgq.sendMessage();
    try {
        msgq >> body;
    } catch (MsgQueue::Error::DiversError &e) {
        cr_assert_eq(e.what(), "Error with shell description");
    }
}