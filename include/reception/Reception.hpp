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

    struct KichenManager {
        OneKitchen kitchen;
        MsgQueue::MessageQueue msgq;
    };

    using KitchenArray = std::vector<KichenManager>;

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
    };

} // ReceptionArea


#endif // _RECEPTION_HPP
