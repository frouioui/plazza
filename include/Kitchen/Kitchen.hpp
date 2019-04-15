/*
** EPITECH PROJECT, 2019
** CPP_plazza_2018
** File description:
** Kitchen class
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

    #include <list>
    #include "Pizza.hpp"
    #include "Stock.hpp"
    #include "SafeThread.hpp"

    /**
     * \namespace Kitchen
     * \brief All elem that are necessary to a Kitchen
     */
    namespace Kitchen {

        /**
         * \class Kitchen
         * \brief Kitchen containt Cook that produce Pizza
         */
        class Kitchen {
            public:

                /**
                 * \brief Constructor
                 * \param[in] nbCooks --> Program Param
                 * \param[in] link between the reception and the Kitchen
                 */
                Kitchen(const int nbCooks/*TODO IPC IDENTIFIER*/);

                /**
                 * Deconstructor
                 */
                ~Kitchen();

            private:
                int _maxPizza;
                SafeThread<std::list<Pizza::Pizza &>> _toDo;
                SafeThread<std::list<Pizza::Pizza &>> _finished;
                SafeThread<Stock> _stock;
                /* TODO CONTAINER FOR THREADED COOK */
        };

    };

#endif /* !KITCHEN_HPP_ */
