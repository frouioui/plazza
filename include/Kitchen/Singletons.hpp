/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** Singletons
*/

#ifndef SINGLETONS_HPP_
    #define SINGLETONS_HPP_

template<typename T>
class Singleton {
    public:
        static T &get();

        Singleton(const Singleton&) = delete;
        Singleton &operator=(const Singleton) = delete;

    private:
        Singleton() {}
};

#include <memory>
template<typename T>
T& Singleton<T>::get()
{
    static const std::unique_ptr<T> instance{new T};
    return *instance;
}
#endif /* !SINGLETONS_HPP_ */
