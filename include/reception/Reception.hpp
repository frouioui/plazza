/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Main header of the reception
*/

#if !defined(_RECEPTION_HPP)
#define _RECEPTION_HPP

#include "reception/Shell.hpp"
#include "Kitchen/Kitchen.hpp"
#include "MessageQueue.hpp"

namespace ReceptionArea
{

    using OneKitchen = Kitchen::Kitchen;

    // Refers to a proccess
    struct KitchenManager {
        MsgQueue::MessageQueue msgq;
    };

    using KitchenArray = std::vector<KitchenManager>;

    class Reception
    {
    public:
        Reception();
        ~Reception();

        void setValues(const int argc, const char *argv[]) throw();
        void launch() throw();

    private:
        float           _multiplier;
        unsigned int    _nbCook;
        long            _replaceTime;
        Shell::Shell    _shell;

        KitchenArray    _kitchens;

        void sendStatus();
        void sendCommands(const std::vector<Pizza::Command> commands);
        void createKitchen();
    };

} // ReceptionArea


#endif // _RECEPTION_HPP
