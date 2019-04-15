/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Stock
*/

#ifndef STOCK_HPP_
    #define STOCK_HPP_

    #include <array>
    #include <chrono>
    #include "Pizza.hpp"

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
                Stock();

                /**
                 * \brief Deconstructor
                 */
                ~Stock();

                bool check_Stock_Ingrediant_Pizza(Pizza::Pizza &pizza);

                bool update(void);

            protected:
            private:
                std::array<std::size_t, Ingredient::MAX_NB_INGREDIANT> _ingrediantRemaining;
        };

    };

#endif /* !STOCK_HPP_ */
