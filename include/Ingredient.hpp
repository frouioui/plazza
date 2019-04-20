/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Ingredient
*/

#ifndef INGREDIENT_HPP_
    #define INGREDIENT_HPP_

#include <string>

/**
 * \class Ingredient
 * \brief Ingredient needed for Pizza
 */
struct Ingredient {
    using CookingTime = int;
    using Name = std::string;

    const Name name;
    const CookingTime cookingTime;
};


#endif /* !INGREDIENT_HPP_ */
