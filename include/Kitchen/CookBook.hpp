/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** CookBook
*/

#ifndef COOKBOOK_HPP_
    #define COOKBOOK_HPP_

#include <vector>
#include <map>
#include "Ingrediant.hpp"
#include "Command.hpp"
#include "Singletons.hpp"

namespace Kitchen {

    /**
     * \class CookBook
     * \brief List all recipe for Pizza
     */
    class CookBook {
        public:
            CookBook() {};
            ~CookBook() {};

            using Recipe = std::vector<Ingrediant>;
            using CookingTime = int;

            Recipe &getRecipe(Pizza::Command &command) {/* TODO */(void)command;return tmp;};

            CookingTime &getCookingTime(Pizza::Command &command) {/* TODO */ (void)command;return tmp1;};

        protected:
        private:
            static constexpr const char *_configPath = "./.plazza/Pizza.conf";
            std::map<std::string, Recipe> _recipes;
            std::map<std::string, CookingTime> _cookingTime;
            Recipe tmp; /* TODO Remove */
            CookingTime tmp1; /* TODO Remove */
    };

};

#endif /* !COOKBOOK_HPP_ */
