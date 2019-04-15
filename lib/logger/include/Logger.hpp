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

namespace Log
{

    class Logger
    {
    public:
        Logger();
        Logger(const std::string &path);
        ~Logger();

        void important(const std::string &msg) noexcept;
        void info(const std::string &msg) noexcept;

    private:
        bool _stdout;
        std::ofstream _outfile;
        std::string _path;
    };

} // Logger


#endif // _LOGGER_HPP
