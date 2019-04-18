/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Stock
*/

#ifndef STOCK_HPP_
    #define STOCK_HPP_

    #include <array>
    #include <mutex>
    #include "Command.hpp"
    #include "CookBook.hpp"
    #include "Singletons.hpp"

    namespace Kitchen {

        enum Ingredient {
            DOE,
            TOMATO,
            GRUYERE,
            HAM,
            MUSHROOMS,
            STEAK,
            EGGPLANT,
            GOATCHEESE,
            CHIEFLOVE,
            MAX_NB_INGREDIANT
        };

        /**
         * \class Stock
         * \brief Stock all the ingredient and refill the stocks when needed
         */
        class Stock {
            public:
                /**
                 * \brief Constructor
                 */
                Stock() {};

                /**
                 * \brief Deconstructor
                 */
                ~Stock() = default;

                bool checkStockForRecipe(CookBook::Recipe &pizza) {/* TODO */(void)pizza;return true;};

                bool update(void) /* TODO or maybe make it private and update on a call to the instance*/;

            protected:
            private:
                std::array<std::size_t, Ingredient::MAX_NB_INGREDIANT> _ingrediantRemaining;
        };

    };

#endif /* !STOCK_HPP_ */
