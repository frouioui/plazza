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
#include "MessageQueue.hpp"
#include "Logger.hpp"

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
            Kitchen(float multiplier, size_t nbCooks, long timeReplace, MsgQueue::MessageQueue &msgQueue);
            Kitchen(const Kitchen &old);
            ~Kitchen();

            float getMultiplier() const;
            size_t getNbCooks() const;
            long getTimeReplace() const;
            const MsgQueue::MessageQueue &getMsgQueue() const;

        private:
            SafeThread<std::list<Pizza::Command *>> _toDo;
            SafeThread<std::list<Pizza::Command *>> _finished;

            SafeThread<Stock> _stock;

            float _multiplier; /*!< Cooking time multiplier */

            size_t _nbCooks; /*!< Number of cooks in the kitchen */
            std::list<Cook> _cooks; /*!< Cook threads */

            long _timeReplace; /*!< Time to replace ingredient on stock */

            MsgQueue::MessageQueue _msgQueue; /*!< Message Queue */

            size_t _maxPizza; /*!< Maximum number of pizza that can b cooked at the same moment */

            bool _saturated; /*!< True if kitchen is saturated, otherwise false */

            std::chrono::time_point<std::chrono::system_clock> _time; /*!< Kitchen must close after 5 sec of inactivity*/

            Log::Logger _log;

            /**
             * \brief Launch Cook thread
             *
             * Create Cook threads, which launch directy
             */
            void startCooking() noexcept;

            bool CookisCooking(void) noexcept;
            size_t CookisFree(void) noexcept;

            /**
             * \brief Stop Cook thread
             *
             * Join Cook threads and quit Kitchen
             */
            void stopCooking() noexcept;
            /**
             * \brief Display the kitchen status
             *
             * Display current occupancy of the cooks and
             * theirs stocks of ingredient.
             * This methods is called using the 'status' user command.
             */
            void displayStatus() const noexcept;


            /**
             * \brief Send ready order to the reception
             */
            void sendReadyOrder() noexcept;

            /**
             * \brief Send empty message in message queue
             */
            void sendEmptyMsg();

            /**
             * \brief Add order to a list of pizza to cook
             *
             * \param pizza Pizza to cook
             */
            void addOrder(const MsgQueue::BodyMsg &msg) noexcept;
            void sendImDying(MsgQueue::Message &response);
            void getFreeSlot(MsgQueue::Message &response);
            void executeRequest(const MsgQueue::BodyMsg &request) noexcept;
            /**
             * \brief Calculate saturation indicator
             */
            size_t calculSaturation() noexcept;

            /**
             * \brief Check if the Kitchen afk more then X time
             */
            bool CheckAfkForTooLong(void);
    };

};

#endif /* !KITCHEN_HPP_ */