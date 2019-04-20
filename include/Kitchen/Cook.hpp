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
    class Cook {
        public:
            /**
             * \brief Constructor of a Cook Who Need what he can do
             */
            explicit Cook(
                SafeThread<std::list<Pizza::Command *>> &toDo,
                SafeThread<std::list<Pizza::Command *>> &finished
            );

            /**
             * \brief Check if the Cook is Busy
             * \return true if the Cook is Busy
             */
            bool isBusy();

            /**
             * \brief DeConstructor
             */
            ~Cook();

            void Start(void);

            void Stop(void);

        protected:
        private:
            Pizza::Command cookPizza(void);
            bool _stop;
            Pizza::Command *_current;
            SafeThread<std::list<Pizza::Command *>> &_toDo;
            SafeThread<std::list<Pizza::Command *>> &_finished;
            std::thread _thread;
    };

};

#endif /* !COOK_HPP_ */