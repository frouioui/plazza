/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** COMMAND
*/

#ifndef COMMAND_HPP_
    #define COMMAND_HPP_

    #include <exception>
    #include <string>
    #include "MessageQueue.hpp"

/**
 * \namespace Pizza
 * \brief All Data Pizza
 */
namespace Pizza {

    /**
     * \enum Size
     * \brief Size of Pizza
     */
    enum Size {
        S = 1,/*!< Small size */
        M = 2,/*!< Medium size */
        L = 4,/*!< Large size */
        XL = 8,/*!< Extra large size */
        XXL = 16,/* Extra extra large size */
    };

    enum Type
    {
        Regina = 1 ,
        Margarita = 2 ,
        Americana = 4 ,
        Fantasia = 8
    };

    /**
     * \struct Command::Command
     * \brief Command Data (type and size)
     */
    struct Command {
        const Pizza::Type _name;/*<! Name of the Pizza */
        const Pizza::Size _size;/*!< Size of the Pizza */
    };

    Type getTypeFromString(const std::string &str);

    bool isAType(std::string &str);

    bool isASize(std::string &str);

    Size getSizeFromString(const std::string &str);

    std::string getStringFromType(const Pizza::Type &type);
    std::string getStringFromSize(const Pizza::Size &size);

    class Error : std::exception {
        std::string _msg;
        public:
            Error(const std::string &msg) : _msg(msg) {};
            ~Error() = default;

            const char *what(void) const noexcept override {    return _msg.c_str();    };
    };

    MsgQueue::Message &operator<<(MsgQueue::Message &msg, Command &cmd);

};

#endif /* !PIZZA_HPP_ */
