/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Cook
*/

#ifndef COOK_HPP_
    #define COOK_HPP_

#include <list>
#include <thread>
#include "Kitchen/Stock.hpp"
#include "Kitchen/SafeThread.hpp"

namespace Kitchen {

/**
 * \class Cook
 * \brief is the One Who Cook the Pizza
 */
    class Cook  : public std::thread {
        public:
            /**
             * \brief Constructor of a Cook Who Need what he can do
             */
            explicit Cook(
                SafeThread<std::list<Pizza::Command *>> &toDo,
                SafeThread<std::list<Pizza::Command *>> &finished);

            /**
             * \brief DeConstructor
             */
            ~Cook();

            Pizza::Command cookPizza(void);

            void Stop(void);

        protected:
        private:
            bool _stop;
            Pizza::Command *_current;
            SafeThread<std::list<Pizza::Command *>> &_toDo;
            SafeThread<std::list<Pizza::Command *>> &_finished;
    };

};

#endif /* !COOK_HPP_ */