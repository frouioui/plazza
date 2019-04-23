/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** CookBook
*/

#include <sstream>
#include <iostream>
#include "ConfigReader.hpp"
#include "Kitchen/Error.hpp"
#include "Kitchen/CookBook.hpp"

static std::vector<Ingrediant> split(std::string s, char c)
{
   std::vector<Ingrediant> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, c))
   {
      tokens.push_back({token});
   }
   return tokens;
}


Kitchen::CookBook::CookBook()
{
    ConfigurationReader::config_t config = ConfigurationReader::ConfigReader(_configPath).getConfig();
    for (auto line : config) {
        auto index = line.first.find("_INGREDIANT");
        if (index != std::string::npos) {
            this->_recipes[line.first.substr(0, index)] = split(line.second, ',');
            continue;
        }
        index = line.first.find("_COOKINGTIME");
        if (index != std::string::npos) {
            this->_cookingTime[line.first.substr(0, index)] = std::stoi(line.second);
        }
    }
}

void Kitchen::CookBook::setMultiplier(int mult)
{
    _mult = mult;
}

Kitchen::CookBook::CookingTime Kitchen::CookBook::getCookingTime(Pizza::Command &command)
{
    std::string pizza_name = command._name;
    for (auto c = pizza_name.begin(); c != pizza_name.end(); c++)
        *c = toupper(*c);
    if (_cookingTime.count(pizza_name) == 0)
        throw Kitchen::Error("Unknow Pizza Name");
    return _cookingTime.at(pizza_name) * _mult;
}

Kitchen::CookBook::Recipe &Kitchen::CookBook::getRecipe(Pizza::Command &command)
{
    std::string pizza_name = command._name;
    for (auto c = pizza_name.begin(); c != pizza_name.end(); c++)
        *c = toupper(*c);
    if (_recipes.count(pizza_name) == 0)
        throw Kitchen::Error("Unknow Pizza Name");
    return _recipes.at(pizza_name);
}

Kitchen::CookBook::~CookBook()
{
}
