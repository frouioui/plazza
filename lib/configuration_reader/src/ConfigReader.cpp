/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the ConfigReader class
*/


#include <unordered_map>
#include <fstream>
#include "ConfigReader.hpp"
#include "ConfigReaderError.hpp"

using namespace ConfigurationReader;

ConfigReader::ConfigReader()
{
}

ConfigReader::ConfigReader(const std::string &path) :
    _path(path)
{
}

ConfigReader::~ConfigReader()
{
}

void ConfigReader::setPath(const std::string &path) noexcept
{
    _path = path;
}

const config_t ConfigReader::getConfig() const
{
    config_t ret;
    size_t pos = 0;
    std::ifstream file(_path);
    std::string line;

    if (file.is_open() == false) {
        throw Error::FileError{"Cannot open the given file", "getConfig"};
    }
    while (file.eof() == false) {
        getline(file, line);
        if (isLineComment(line) == true || isLineUseful(line) == false)
            continue;
        pos = line.find_first_of('=');
        if (pos == std::string::npos)
            throw Error::FileContentError{"The file is malformated", "getConfig"};
        ret[line.substr(0, pos)] = line.substr(pos + 1);
    }
    return ret;
}

bool ConfigReader::isLineComment(const std::string &line) const noexcept
{
    unsigned int i = 0;

    while (i < line.size() && std::isspace(line[i]) == true) {
        i++;
    }
    if (line[i] == '#') {
        return true;
    }
    return false;
}

bool ConfigReader::isLineUseful(const std::string &line) const noexcept
{
    size_t pos = 0;

    while (pos < line.size() && std::isspace(line[pos]))
        pos++;
    return !(pos == line.size());
}