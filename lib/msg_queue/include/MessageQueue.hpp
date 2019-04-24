/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Header file of the Message queue class
*/

#if !defined(_MESSAGE_QUEUE_HPP)
#define _MESSAGE_QUEUE_HPP

#include <string>
#include <sys/types.h>
#include <sys/ipc.h>

namespace MsgQueue
{

    enum MsgType: long {
        UNDEFINED = 0,
        KITCHEN = 1,
        RECEPTION = 2
    };

    struct Message {
        MsgType type;
        char msg[BUFSIZ];
    };

    enum BodyType {
        CMD,
        ERROR,
        SHELL,
        RESP,
        DELY
    };

    struct BodyMsg {
        BodyType type;
        std::string descrpt;
        std::string value;
    };

    class MessageQueue
    {
    public:
        MessageQueue();
        MessageQueue(const int id, const std::string &path = "./msg_queue"); //TODO: set default path
        ~MessageQueue();

        // Direct call to C library function
        key_t generateKey(const std::string &path, const int id) const throw();
        int createQueue(const key_t &key) const throw();
        int sendMessage(const Message &msg, const int id) const throw();
        ssize_t receiveMessage(Message &msg, const int id) const throw();
        void destroyQueue(const int id) const throw();

        // Using the current class's data
        key_t generateKey() throw();
        int createQueue() throw();
        int sendMessage() throw();
        ssize_t receiveMessage() throw();
        void destroyQueue() throw();

        // Getters and Setters
        Message getLastReceived() const noexcept;
        void setMsgToSend(const Message &msg) noexcept;
        void setMsgType(MsgType type) noexcept;
        MsgType getMsgTypeToSend() const noexcept;

    private:
        std::string _path;
        int _id;
        key_t _key;
        int _idQueue;
        Message _msgSend;
        Message _msgReceive;
        MsgType _msgType;
    };

    MessageQueue &operator>>(MessageQueue &msgQueue, BodyMsg &body);
    MessageQueue &operator<<(MessageQueue &msgQueue, Message &msg);
} // MsgQueue


#endif // _MESSAGE_QUEUE_HPP
