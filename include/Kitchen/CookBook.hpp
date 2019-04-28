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
#include "Ingredient.hpp"
#include "Command.hpp"
#include "Singletons.hpp"

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
            using CookingTime = int;

            void setMultiplier(const float mult);

            Recipe &getRecipe(Pizza::Command &command);

            CookingTime getCookingTime(Pizza::Command &command);

        protected:
        private:
            static constexpr const char *_configPath = "./.plazza/Pizza.conf";
            std::map<std::string, Recipe> _recipes;
            std::map<std::string, CookingTime> _cookingTime;
            float _mult;
    };

};

#endif /* !COOKBOOK_HPP_ */
