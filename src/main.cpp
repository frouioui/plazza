/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** main
*/

#include <iostream>
#include "reception/Reception.hpp"
#include "reception/Error.hpp"

// int main(const int argc, const char *argv[])
// {
//     ReceptionArea::Reception resp;

//     try {
//         resp.setValues(argc, argv);
//     } catch (ReceptionArea::Error::InvalidArgument &e) {
//         // DEBUG: if one or more argument are invalid
//         std::cout << e.what() << std::endl;
//         std::cout << "Try using the -h option." << std::endl;
//         return (84);
//     } catch (ReceptionArea::Error::Helper &e) {
//         // DEBUG: if the '-h'/'--help' option was found
//         // helper();
//         std::cout << e.what() << std::endl;
//         return (0);
//     }

//     // DEBUG: start the simulation here
//     resp.launch();

//     return (0);
// }

#include "Kitchen/CookBook.hpp"

int main(void)
{
    Kitchen::CookBook tmp;
    Pizza::Command command = {"Regina", Pizza::Size::XXL};
    Kitchen::CookBook::Recipe recipe = {{"DOE"}, {"TOMATE"}, {"GRUYERE"}, {"HAM"}, {"MUSHROOMS"}};

    tmp.getCookingTime(command);
}