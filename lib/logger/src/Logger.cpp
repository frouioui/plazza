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
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    if (_stdout) {
        std::cout << std::ctime(&end_time) << " [IMPORTANT] - " << msg << std::endl;
    } else {
        _outfile << std::ctime(&end_time) << " [IMPORTANT] - " << msg << std::endl;
    }
}

void Logger::info(const std::string &msg) noexcept
{
    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    if (_stdout) {
        std::cout << std::ctime(&end_time) << " [INFO] - " << msg << std::endl;
    } else {
        _outfile << std::ctime(&end_time) << " [INFO] - " << msg << std::endl;
    }
}