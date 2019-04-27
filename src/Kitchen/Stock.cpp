/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Stock
*/

#include <vector>
#include <sstream>
#include <iostream>
#include "ConfigReader.hpp"
#include "Kitchen/Stock.hpp"
#include "Kitchen/Error.hpp"

static std::vector<std::string> split(std::string s, char c)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, c))
   {
      tokens.push_back(token);
   }
   return tokens;
}

Kitchen::Stock::Stock() :
_multiplier(1000)
{
    std::string allIngrediantVarName = "INGREDIANTS";
    ConfigurationReader::config_t config = ConfigurationReader::ConfigReader(_configPath).getConfig();
    if (config.count(allIngrediantVarName) == 0)
        throw Error("Cant't find " + allIngrediantVarName + " variable in config ingrediants file: " + std::string(_configPath));
    auto allIngrediant = split(config.at(allIngrediantVarName), ',');
    if (!allIngrediant.size())
        throw Error("No Ingrediant check you config file: " + std::string(_configPath));
    for (auto ingrediant : allIngrediant)
        _stock[ingrediant] = _defaultQuantity;
    _time = std::chrono::system_clock::now();
}

void Kitchen::Stock::setMultiplier(const long multiplier)
{
    _multiplier = multiplier;
}

std::string Kitchen::Stock::displayStock(void)
{
    std::string infoStock =  "------ Stock of ingredients ------\n";
    _safe_stock.lock();
    for (auto ingrediant : _stock)
        infoStock += "\t" + ingrediant.first + ": " + std::to_string(ingrediant.second) + '\n';
    _safe_stock.unlock();
    return infoStock;
}

int Kitchen::Stock::timeToRefill(void)
{
    _safe_time.lock();
    auto now = std::chrono::system_clock::now();
    auto elapsedTime = now - _time;
    int res = 0;
    if (elapsedTime > std::chrono::milliseconds(1) * _multiplier) {
        _time = now;
        res = elapsedTime / std::chrono::milliseconds(1) * _multiplier;
    }
    _safe_time.unlock();
    return res;
}

void Kitchen::Stock::tryRefillStock(void)
{
    int toadd = timeToRefill();
    if (toadd) {
        _safe_stock.lock();
        for (auto &ingrediant : _stock) {
            ingrediant.second += toadd;
            if (ingrediant.second > 5)
                ingrediant.second = 5;
        }
        _safe_stock.unlock();
    }
}

bool Kitchen::Stock::getRecipe(CookBook::Recipe &pizza)
{
    tryRefillStock();
    _safe_stock.lock();
    for (auto ingrediant : pizza) {
        if (_stock.at(ingrediant.name) == 0) {
            _safe_stock.unlock();
            return false;
        }
    }
    for (auto &ingrediant : pizza)
        _stock[ingrediant.name] -= 1;
    _safe_stock.unlock();
    return true;
}

Kitchen::Stock::~Stock()
{
}
