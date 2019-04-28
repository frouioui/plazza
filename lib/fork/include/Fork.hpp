/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Definition of the fork class
*/

#if !defined(_FORK_HPP)
#define _FORK_HPP

#include <sys/types.h>

namespace Fork
{

    class Forker
    {
    public:
        Forker();
        ~Forker();

        pid_t forkProcess();
    };

} // Fork


#endif // _FORK_HPP
