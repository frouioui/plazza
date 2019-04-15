/*
** EPITECH PROJECT, 2019
** CPP_plazza_2018
** File description:
** Cook class
*/

#ifndef COOK_HPP_
    #define COOK_HPP_

#include "Pizza.hpp"
class Cook {
    public:
        Cook();
        ~Cook() = default;

        Pizza::Pizza cookPizza();
        void getPizzaToCook(Pizza::Pizza);
    private:
        bool _free;
};

#endif /* !COOK_HPP_ */
