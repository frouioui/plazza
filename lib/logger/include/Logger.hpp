/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Header of the Logger class
*/

#if !defined(_LOGGER_HPP)
#define _LOGGER_HPP

#include <fstream>
#include <string>

namespace Logger
{

    class Logger
    {
    public:
        Logger(const std::string &path);
        ~Logger();

        void important(const std::string &msg) const noexcept;
        void info(const std::string &msg) const noexcept;

    private:
        std::ifstream _file;
        std::string _path;
    };

} // Logger


#endif // _LOGGER_HPP
