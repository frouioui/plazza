/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Stock
*/

#ifndef STOCK_HPP_
    #define STOCK_HPP_

    #include <map>
    #include <mutex>
    #include "Command.hpp"
    #include "CookBook.hpp"

    namespace Kitchen {

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

                /**
                 * \brief Set the refill time
                 * \param[in] multiplier 1s * multiplier
                 */
                void setMultiplier(const int multiplier);

                /**
                 * \brief check if the recipe is available and remove ingrediant if it's the case
                 * \param[in] Recipe of the Pizza
                 * \return true if there is enought Ingrediant false otherwise
                 */
                bool getRecipe(CookBook::Recipe &pizza);

                /**
                 * \brief display the Current Quantity of Ingrediant
                 */
                void displayStock(void);

            protected:
            private:
                void tryRefillStock(void);
                std::map<Ingrediant::Name, int> _stock;
                static constexpr const char *_configPath = "./plazza/Ingrediant.conf";
                static constexpr const int _defaultQuantity = 5;
                std::chrono::time_point<std::chrono::system_clock> _time;
                std::mutex _safe_time;
                std::mutex _safe_stock;
                int _multiplier;
                int timeToRefill(void);
        };

    };

#endif /* !STOCK_HPP_ */