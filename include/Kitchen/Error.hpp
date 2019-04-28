/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Error
*/

#ifndef ERROR_HPP_
    #define ERROR_HPP_

#include <exception>
#include <string>

namespace Kitchen {


    class Error : std::exception {
        public:
            Error(const std::string &msg) : _msg(msg) {};
            ~Error() = default;

            const char *what(void) const noexcept override {    return _msg.c_str();    };

        protected:
            std::string _msg;
        private:
    };

};

#endif /* !ERROR_HPP_ */
