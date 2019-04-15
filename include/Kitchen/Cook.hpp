/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_

    #include <list>
    #include "Kitchen/Stock.hpp"
    #include "Kitchen/SafeThread.hpp"

    namespace Kitchen {

        /**
         * \class Cook
         * \brief is the One Who Cook the Pizza
         */
        class Cook {
            public:
                /**
                 * \brief Constructor of a Cook Who Need what he can do
                 */
                explicit Cook(SafeThread<Stock> &stock, SafeThread<std::list<Pizza::Pizza &>> &toDo, SafeThread<std::list<Pizza::Pizza &>> &finished);

                /**
                 * \brief DeConstructor
                 */
                ~Cook();

            protected:
            private:
                SafeThread<Stock> &_stock;
                SafeThread<std::list<Pizza::Pizza *>> &_toDo;
                SafeThread<std::list<Pizza::Pizza *>> &_finished;
        };

    };

#endif /* !COOK_HPP_ */
