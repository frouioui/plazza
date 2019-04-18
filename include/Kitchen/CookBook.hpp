/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** CookBook
*/

#ifndef COOKBOOK_HPP_
    #define COOKBOOK_HPP_

#include <vector>
#include "Ingrediant.hpp"
#include "Command.hpp"

namespace Kitchen {

    /**
     * \class CookBook
     * \brief List all recipe for Pizza
     */
    class CookBook {
        public:
            CookBook();
            ~CookBook();

        using Recipe = std::vector<Ingrediant>;

        Recipe &getRecipe(Pizza::Command &command);

        protected:
        private:
    };

};

#endif /* !COOKBOOK_HPP_ */
