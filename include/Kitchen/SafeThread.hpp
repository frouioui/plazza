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
    class SafeThread : public std::mutex {
        public:
            SafeThread();
            ~SafeThread();

            T &operator->(void)
            {
                if (!this->try_lock())
                    throw Error("Can't Lock");
                return _Safe;
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
            std::mutex list_lock;
            T _Safe;
        private:
    };

#endif /* !SAFETHREAD_HPP_ */
