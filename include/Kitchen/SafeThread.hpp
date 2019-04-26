/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** SafeThread
*/

#ifndef SAFETHREAD_HPP_
    #define SAFETHREAD_HPP_

    #include <mutex>

    /**
     * \class SafeThread
     */
    template<class T>
    class SafeThread {
        public:
            SafeThread() : _ImLock(false) {};
            ~SafeThread() = default;

            void lock() noexcept
            {
                _mutex.lock();
                _ImLock = true;
            };

            void unlock() noexcept
            {
                _mutex.unlock();
                _ImLock = false;
            };

            bool try_lock() noexcept
            {
                bool res = _mutex.try_lock();
                if (res)
                    _ImLock = true;
                return res;
            };

            T *operator->(void)
            {
                // if (!_ImLock)
                //     throw Error("Can't use me i'm not lock");
                return &_Safe;
            }

            class Error : public std::exception {
                public:
                    Error(const std::string &msg) : _msg(msg) {};
                    ~Error() = default;

                    const char *what(void) const noexcept   {   return _msg.c_str();   };
                private:
                    std::string _msg;
            };

        protected:
            T _Safe;
            bool _ImLock;
            std::mutex _mutex;
        private:
    };

#endif /* !SAFETHREAD_HPP_ */
