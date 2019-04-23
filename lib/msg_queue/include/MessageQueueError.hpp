/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ConfigReader errors and throw
*/

#if !defined(_MESSAGE_QUEUE_ERROR_HPP)
#define _MESSAGE_QUEUE_ERROR_HPP

#include <exception>
#include <iostream>

namespace MsgQueue
{

    namespace Error
    {

        class MsgQueueError : public std::exception
        {
        public:
            MsgQueueError(const std::string &msg, const std::string &where = "Unknown");
            virtual ~MsgQueueError() throw() {};

            const char *what() const noexcept override;
            const char *where() const noexcept;

        protected:
            std::string _where;
        private:
            std::string _what;
        };

        class DiversError : public MsgQueueError
        {
        public:
            DiversError(std::string const &message, std::string const &where = "Unknown") : MsgQueueError(message, where) {};
            virtual ~DiversError() throw() {};
        };

    } // Error

} // MsgQueue


#endif // _MESSAGE_QUEUE_ERROR_HPP