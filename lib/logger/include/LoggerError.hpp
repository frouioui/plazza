/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ConfigReader errors and throw
*/

#if !defined(_LOGGER_ERROR_HPP)
#define _LOGGER_ERROR_HPP

#include <exception>
#include <iostream>

namespace Log
{

    namespace Error
    {

        class LoggerError : public std::exception
        {
        public:
            LoggerError(const std::string &msg, const std::string &where = "Unknown");
            virtual ~LoggerError() throw() {};

            const char *what() const noexcept override;
            const char *where() const noexcept;

        protected:
            std::string _where;
        private:
            std::string _what;
        };

        class FileError : public LoggerError
        {
        public:
            FileError(std::string const &message, std::string const &where = "Unknown") : LoggerError(message, where) {};
            virtual ~FileError() throw() {};
        };

    } // Error

} // Log


#endif // _LOGGER_ERROR_HPP