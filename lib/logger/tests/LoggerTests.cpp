/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test file of the logger class
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "Logger.hpp"
#include "LoggerError.hpp"

using namespace Log;

Test(logger_constructor, default_ctor)
{
    Logger log;
}

Test(logger_constructor, param_ctor)
{
    std::ofstream("test");
    Logger log("test");
    remove("test");
}

Test(logger_setpath, unknown_file_ctor)
{
    cr_assert_throw(Logger log("toto"), Error::FileError);
    remove("toto");
}

Test(logger_getConfig, important_log_stdout)
{
    Logger log;

    cr_redirect_stdout();
    log.important("Test");
    cr_assert_stdout_eq_str("[IMPORTANT] - Test\n");
}

Test(logger_getConfig, info_log_stdout)
{
    Logger log;

    cr_redirect_stdout();
    log.info("Test");
    cr_assert_stdout_eq_str("[INFO] - Test\n");
}

Test(logger_getConfig, important_log_file)
{
    Logger log("test");

    log.important("Test");
    std::fstream file("test");
    std::string line;
    getline(file, line);
    cr_assert_str_eq(line.c_str(), "[IMPORTANT] - Test");
    remove("test");
}

Test(logger_getConfig, info_log_file)
{
    Logger log("test");

    log.info("Test");
    std::fstream file("test");
    std::string line;
    getline(file, line);
    cr_assert_str_eq(line.c_str(), "[INFO] - Test");
    remove("test");
}
