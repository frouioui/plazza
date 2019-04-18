/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Source file of the Reception class
*/

#include "reception/Reception.hpp"
#include "reception/Error.hpp"
#include "StringParser.hpp"

using namespace ReceptionArea;

Reception::Reception()
{
}

Reception::~Reception()
{
}

void Reception::setValues(const int argc, const char *argv[]) throw()
{
    std::string shelp = "-h";
    std::string lhelp = "--help";

    if (argc == 2 && (shelp.compare(argv[1]) == 0 || lhelp.compare(argv[1]) == 0)) {
        throw Error::Helper("Display helper", "setValues");
    } else if (argc != 4) {
        throw Error::InvalidArgument("Invalid argument, need at least 4 arguments.", "setValues");
    }
    std::string coefstr(argv[1]);
    std::string cookstr(argv[2]);
    std::string timestr(argv[3]);

    if (coefstr.find_first_not_of(".0123456789") != std::string::npos ||
        cookstr.find_first_not_of("0123456789") != std::string::npos ||
        timestr.find_first_not_of("0123456789") != std::string::npos ) {
        throw Error::InvalidArgument("Argument must be positiv float value or integers.", "setValues");
    }
    if (coefstr.find_first_of(".") != std::string::npos) {
        _multiplier = std::atof(coefstr.c_str());
        if (!(_multiplier > 0 && _multiplier < 1)) {
            throw Error::InvalidArgument("The multiplier should be between 0.00 and 1.00.", "setValues");
        }
    } else {
        _multiplier = (float)std::atoi(coefstr.c_str());
    }
    _nbCook = std::atoi(cookstr.c_str());
    _replaceTime = std::atol(timestr.c_str());
}

void Reception::launch() throw()
{
    ReceptionArea::Shell::InputType inputType;

    while (_shell.isDone() == false) {
        inputType = _shell.readLine();
        if (inputType == ReceptionArea::Shell::OTHER) {
            Pizza::Pizza parsePizza = _shell.parsePizza();
            (void)parsePizza;
        } else if (inputType == ReceptionArea::Shell::HELPER) {
            // TODO: Display helper in the shell
        }
    }
}