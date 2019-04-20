/*
** EPITECH PROJECT, 2019
** Plazza
** File description:
** Test file of the reception's setvalue method
*/

#include <criterion/criterion.h>
#include <criterion/assert.h>
#include <exception>
#include <stdlib.h>
#include "reception/Reception.hpp"
#include "reception/Error.hpp"

Test(setValues, valid_values)
{
    ReceptionArea::Reception resp;
    char **argv = (char **)malloc(sizeof(char *) * 5);

    argv[0] = (char *)std::string("./plazza").c_str();
    argv[1] = (char *)std::string("5").c_str();
    argv[2] = (char *)std::string("10").c_str();
    argv[3] = (char *)std::string("5000").c_str();
    argv[4] = NULL;
    resp.setValues(4, (const char **)argv);
}

// Test(setValues, invalid_number_of_args)
// {
//     ReceptionArea::Reception resp;
//     char **argv = (char **)malloc(sizeof(char *) * 4);

//     argv[0] = (char *)std::string("./plazza").c_str();
//     argv[1] = (char *)std::string("5").c_str();
//     argv[2] = (char *)std::string("10").c_str();
//     argv[3] = NULL;
//     try {
//         resp.setValues(3, (const char **)argv);
//     } catch (std::exception &e) {
//         cr_assert_eq(1, 1);
//     }
//     cr_assert_eq(1, 0);
// }

// Test(setValues, letter_instead_number_invalid)
// {
//     ReceptionArea::Reception resp;
//     char **argv = (char **)malloc(sizeof(char *) * 5);

//     argv[0] = (char *)std::string("./plazza").c_str();
//     argv[1] = (char *)std::string("5").c_str();
//     argv[2] = (char *)std::string("45salut4").c_str();
//     argv[3] = (char *)std::string("10").c_str();
//     argv[4] = NULL;
//     try {
//         resp.setValues(4, (const char **)argv);
//     } catch (ReceptionArea::Error::InvalidArgument &e) {
//         cr_assert_eq(1, 1);
//     }
//     cr_assert_eq(1, 0);}

// Test(setValues, invalid_multiplier)
// {
//     ReceptionArea::Reception resp;
//     char **argv = (char **)malloc(sizeof(char *) * 5);

//     argv[0] = (char *)std::string("./plazza").c_str();
//     argv[1] = (char *)std::string("5.5").c_str();
//     argv[2] = (char *)std::string("45").c_str();
//     argv[3] = (char *)std::string("10").c_str();
//     argv[4] = NULL;
//     try {
//         resp.setValues(4, (const char **)argv);
//     } catch (ReceptionArea::Error::InvalidArgument &e) {
//         cr_assert_eq(1, 1);
//     }
//     cr_assert_eq(1, 0);
// }

Test(setValues, valid_multiplier)
{
    ReceptionArea::Reception resp;
    char **argv = (char **)malloc(sizeof(char *) * 5);

    argv[0] = (char *)std::string("./plazza").c_str();
    argv[1] = (char *)std::string("0.5").c_str();
    argv[2] = (char *)std::string("45").c_str();
    argv[3] = (char *)std::string("10").c_str();
    argv[4] = NULL;
    resp.setValues(4, (const char **)argv);
}