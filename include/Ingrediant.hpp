/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Ingrediant
*/

#ifndef INGREDIANT_HPP_
    #define INGREDIANT_HPP_

#include <string>

/**
 * \class Ingrediant
 * \brief Ingrediant needed for Pizza
 */
struct Ingrediant {
    using CookingTime = int;
    using Name = std::string;

    const Name name;
    const CookingTime cookingTime;
};


#endif /* !INGREDIANT_HPP_ */
