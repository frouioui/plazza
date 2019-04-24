/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** COMMAND
*/

#ifndef COMMAND_HPP_
    #define COMMAND_HPP_

    #include <string>
    #include "MessageQueue.hpp"

/**
 * \namespace Pizza
 * \brief All Data Pizza
 */
namespace Pizza {

    using Type = std::string;

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

    /**
     * \struct Command::Command
     * \brief Command Data (type and size)
     */
    struct Command {
        const Pizza::Type _name;/*<! Name of the Pizza */
        const Pizza::Size _size;/*!< Size of the Pizza */
    };

    MsgQueue::Message &operator<<(MsgQueue::Message &msg, Command &cmd);

};

#endif /* !PIZZA_HPP_ */
