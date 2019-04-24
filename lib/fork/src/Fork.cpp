/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Fork class
*/

#include <unistd.h>
#include <sys/types.h>
#include "Fork.hpp"

using namespace Fork;

Forker::Forker()
{
}

Forker::~Forker()
{
}

pid_t Forker::forkProcess()
{
    return fork();
}