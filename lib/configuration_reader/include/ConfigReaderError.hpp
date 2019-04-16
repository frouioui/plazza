/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** ConfigReader errors and throw
*/

#if !defined(_CONFIG_READER_ERROR_HPP)
#define _CONFIG_READER_ERROR_HPP

#include <exception>
#include <iostream>

namespace ConfigurationReader
{

    namespace Error
    {

        class ConfigReaderError : public std::exception
        {
        public:
            ConfigReaderError(const std::string &msg, const std::string &where = "Unknown");
            virtual ~ConfigReaderError() throw() {};

            const char *what() const noexcept override;
            const char *where() const noexcept;

        protected:
            std::string _where;
        private:
            std::string _what;
        };

        class FileError : public ConfigReaderError
        {
        public:
            FileError(std::string const &message, std::string const &where = "Unknown") : ConfigReaderError(message, where) {};
            virtual ~FileError() throw() {};
        };

        class FileContentError : public ConfigReaderError
        {
        public:
            FileContentError(std::string const &message, std::string const &where = "Unknown") : ConfigReaderError(message, where) {};
            virtual ~FileContentError() throw() {};
        };

    } // Error

} // ConfigurationReader


#endif // _CONFIG_READER_ERROR_HPP
