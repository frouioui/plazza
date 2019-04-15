/*
** EPITECH PROJECT, 2019
** CPP_plazza_2018
** File description:
** Kitchen class
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

#include <vector>
#include <iostream>
#include <pthread.h>
#include "Pizza.hpp"
#include "Cook_c.hpp"

struct ingredient_t {
    std::string name;
    int quantity;
    // Timer;
};

struct pizza_t {
    std::string name;
    // Timer;
};

class Kitchen {
    public:
        Kitchen();
        ~Kitchen() = default;
        /**
         * \brief Display the kitchen status
         *
         * Display current occupancy of the cooks and
         * theirs stocks of ingredient.
         * This methods is called using the 'status' user command.
         */

        void displayStatus() const noexcept;
        /**
         * \brief Indicate if the current kitchen is saturated
         *
         * \return True if the kitchen cannot accept another pizza to cook
         */
        bool isSaturated() const noexcept;

        /**
         * \brief send ready order to the reception
         */
        Pizza::Pizza sendReadyOrder(/*Must be determined*/);
        /**
         * \brief Add order to a list of pizza to cook
         *
         * \param pizza Pizza to cook
         */
        void addOrder(Pizza::Pizza pizza) noexcept;

        /**
         * \brief Assign a pizza to a free cooks
         *
         * Take the first pizza of the pizza list and assign it to a free cooks
         * When a ready order is send to the reception, this method is called.
         */
        void assignPizza();

    private:
        std::vector<Pizza::Pizza> _pizza; /*!< List of pizza to cook */
        std::vector<Cook> _cooks; /*!< Cooks */
        bool _saturated; /*!< True if kitchen is saturated, otherwise false */

        // std::vector<ingredient_t> _ingredients; // init thanks to pizza conf files
        // Timer occupation /*!< Kitchen must close after 5 sec of inactivity*/
        /**
         * \brief Calculate saturation indicator
         */
        void calculStaturation() noexcept;
};

#endif /* !KITCHEN_HPP_ */