/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Header file of the ConfigReader class
*/

#if !defined(_CONFIG_READER_HPP)
#define _CONFIG_READER_HPP

#include <string>
#include <unordered_map>

namespace ConfigurationReader
{

    using config_t = std::unordered_map<std::string, std::string>;

    class ConfigReader
    {
    public:
        ConfigReader();
        ConfigReader(const std::string &path);
        ~ConfigReader();

        void setPath(const std::string &path) noexcept;

        const config_t getConfig() const;

    private:
        bool isLineComment(const std::string &line) const noexcept;
        bool isLineUseful(const std::string &line) const noexcept;
        std::string _path;
    };

} // ConfigurationReader

#endif // _CONFIG_READER_HPP
