/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test file of the ConfigReader class
*/

#include <criterion/criterion.h>
#include <fstream>
#include "ConfigReader.hpp"
#include "ConfigReaderError.hpp"

Test(config_reader_constructor, default_ctor)
{
    ConfigurationReader::ConfigReader cfr;
}

Test(config_reader_constructor, param_ctor)
{
    ConfigurationReader::ConfigReader cfr("./toto");
}

Test(config_reader_setpath, set_simple_path)
{
    ConfigurationReader::ConfigReader cfr;

    cfr.setPath("toto");
}

Test(config_reader_getConfig, simple_config)
{
    ConfigurationReader::config_t conf;
    ConfigurationReader::ConfigReader cfr;
    std::ofstream outfile("config_test.conf");
    outfile << "TOTO=salut" << std::endl;
    outfile.close();

    cfr.setPath("config_test.conf");
    conf = cfr.getConfig();
    cr_assert_eq(conf.empty(), false);
    cr_assert_str_eq(conf["TOTO"].c_str(), "salut");
}

Test(config_reader_getConfig, key_with_no_value)
{
    ConfigurationReader::config_t conf;
    ConfigurationReader::ConfigReader cfr;
    std::ofstream outfile("config_test.conf");
    outfile << "TOTO=" << std::endl;
    outfile.close();

    cfr.setPath("config_test.conf");
    conf = cfr.getConfig();
    cr_assert_eq(conf.empty(), false);
    cr_assert_str_eq(conf["TOTO"].c_str(), "");
}

Test(config_reader_getConfig, multiple_line)
{
    ConfigurationReader::config_t conf;
    ConfigurationReader::ConfigReader cfr;
    std::ofstream outfile("config_test.conf");
    outfile << "TOTO=salut" << std::endl << "HEY=okay" << std::endl;
    outfile.close();

    cfr.setPath("config_test.conf");
    conf = cfr.getConfig();
    cr_assert_eq(conf.empty(), false);
    cr_assert_str_eq(conf["TOTO"].c_str(), "salut");
    cr_assert_str_eq(conf["HEY"].c_str(), "okay");
}

Test(config_reader_getConfig, comment_line)
{
    ConfigurationReader::config_t conf;
    ConfigurationReader::ConfigReader cfr;
    std::ofstream outfile("config_test.conf");
    outfile << "#TOTO=salut" << std::endl;
    outfile.close();

    cfr.setPath("config_test.conf");
    conf = cfr.getConfig();
    cr_assert_eq(conf.empty(), true);
}

Test(config_reader_getConfig, invalid_file_format)
{
    ConfigurationReader::ConfigReader cfr;
    std::ofstream outfile("config_test.conf");
    outfile << "okok=yoyo" << std::endl << "foefoekr" << std::endl;
    outfile.close();

    cfr.setPath("config_test.conf");
    cr_assert_throw(cfr.getConfig(), ConfigurationReader::Error::FileContentError);
}

Test(config_reader_getConfig, invalid_file)
{
    ConfigurationReader::ConfigReader cfr;

    cfr.setPath("toto");
    cr_assert_throw(cfr.getConfig(), ConfigurationReader::Error::FileError);
}