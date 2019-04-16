/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** All the error found in the reception
*/

#if !defined(_ERROR_RECEPTION_HPP)
#define _ERROR_RECEPTION_HPP

#include <string>

namespace ReceptionArea
{

    namespace Error
    {

        class ReceptionError : public std::exception
        {
        public:
            ReceptionError(const std::string &msg, const std::string &where = "Unknown");
            virtual ~ReceptionError() throw() {};

            const char *what() const noexcept override;
            const char *where() const noexcept;

        protected:
            std::string _where;
        private:
            std::string _what;
        };

        class InvalidArgument : public ReceptionError
        {
        public:
            InvalidArgument(std::string const &message, std::string const &where = "Unknown") : ReceptionError(message, where) {};
            virtual ~InvalidArgument() throw() {};
        };

        class Helper : public ReceptionError
        {
        public:
            Helper(std::string const &message, std::string const &where = "Unknown") : ReceptionError(message, where) {};
            virtual ~Helper() throw() {};
        };

    } // Error

} // ReceptionArea


#endif // _ERROR_RECEPTION_HPP
