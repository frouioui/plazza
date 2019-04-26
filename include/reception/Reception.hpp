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
#include "Logger.hpp"

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

        void setValues(const int argc, const char *argv[]);
        void launch();


    private:
        float           _multiplier;
        unsigned int    _nbCook;
        long            _replaceTime;
        Shell::Shell    _shell;

        KitchenArray    _kitchens;

        Log::Logger _logger;


        void sendEmptyMsg();
        void sendStatus();
        void sendCommands(const std::vector<Pizza::Command> commands);
        void createKitchen();
        void checkKitchens();
    };

} // ReceptionArea


#endif // _RECEPTION_HPP
