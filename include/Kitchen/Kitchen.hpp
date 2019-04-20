/*
** EPITECH PROJECT, 2019
** CPP_plazza_2018
** File description:
** Kitchen class
*/

#ifndef KITCHEN_HPP_
    #define KITCHEN_HPP_

#include <list>
#include "Command.hpp"
#include "Stock.hpp"
#include "Cook.hpp"
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
            Kitchen(size_t nbCooks/*, TODO IPC IDENTIFIER*/);

            ~Kitchen();

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
            void sendReadyOrder() noexcept;

            /**
             * \brief Add order to a list of pizza to cook
             *
             * \param pizza Pizza to cook
             */
            void addOrder(Pizza::Command &pizza) noexcept;

        private:
            SafeThread<std::list<Pizza::Command *>> _toDo;
            SafeThread<std::list<Pizza::Command *>> _finished;

            SafeThread<Stock> _stock;

            size_t _nbCooks; /*!< Number of cooks in the kitchen */
            std::list<Cook> _cooks; /*!< Cook threads */

            size_t _maxPizza; /*!< Maximum number of pizza that can b cooked at the same moment */

            bool _saturated; /*!< True if kitchen is saturated, otherwise false */

            // Timer occupation /*!< Kitchen must close after 5 sec of inactivity*/

            /**
             * \brief Launch Cook thread
             *
             * Create Cook threads, which launch directy
             */

            void startCooking() noexcept;
            /**
             * \brief Calculate saturation indicator
             */
            void calculSaturation() noexcept;
    };

};

#endif /* !KITCHEN_HPP_ */