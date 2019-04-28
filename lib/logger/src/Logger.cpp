/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the Logger class
*/

#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
#include "Logger.hpp"
#include "LoggerError.hpp"

using namespace Log;

// TODO: timestamps

Logger::Logger() :
    _stdout(true)
{
}

Logger::Logger(const std::string &path) :
    _stdout(false), _path(path)
{
    _outfile.open(path);
    if (_outfile.is_open() == false) {
        throw Error::FileError{"The file can't be opened", "Logger ctor"};
    }
}

Logger::~Logger()
{
}

void Logger::important(const std::string &msg) noexcept
{
    char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = gmtime (&now);

    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    if (_stdout) {
        std::cout << buff << " [IMPORTANT] - " << msg << std::endl;
    } else {
        _outfile << buff << " [IMPORTANT] - " << msg << std::endl;
    }
}

void Logger::info(const std::string &msg) noexcept
{
    char buff[20];
    struct tm *sTm;

    time_t now = time (0);
    sTm = gmtime (&now);

    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", sTm);
    if (_stdout) {
        std::cout << buff << " [INFO] - " << msg << std::endl;
    } else {
        _outfile << buff << " [INFO] - " << msg << std::endl;
    }
}