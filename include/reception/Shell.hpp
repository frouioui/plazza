/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Header file of the reception's shell
*/

#if !defined(_SHELL_HPP)
#define _SHELL_HPP

#include <string>
#include "Pizza.hpp"

namespace ReceptionArea
{

    namespace Shell
    {

        enum InputType {
            OTHER,
            QUIT,
            HELPER
        };

        class Shell
        {
        public:
            Shell();
            ~Shell();

            bool isDone() const noexcept;
            void writeUser(const std::string &msg) const noexcept;
            InputType readLine() noexcept;
            Pizza::Pizza parsePizza() const;

        private:
            std::string _lastLine;
            bool _done;
        };

    } // Shell

} // ReceptionArea


#endif // _SHELL_HPP
