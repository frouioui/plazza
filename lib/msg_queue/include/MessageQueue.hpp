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

    enum MsgType {
        RECEIVE,
        SEND
    };

    struct Message {
        MsgType type;
        char msg[BUFSIZ];
    };

    enum BodyType {
        CMD,
        ERROR,
        SHELL,
        RESP
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
        MessageQueue(const std::string &path, const int id);
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


    private:
        std::string _path;
        int _id;
        key_t _key;
        int _idQueue;
        Message _msgSend;
        Message _msgReceive;
    };

    MessageQueue &operator>>(MessageQueue &msgQueue, BodyMsg &body) throw();
} // MsgQueue


#endif // _MESSAGE_QUEUE_HPP
