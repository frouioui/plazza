/*
** EPITECH PROJECT, 2019
** plazza
** File description:
** criterion_main
*/

#include <criterion/criterion.h>
#include <criterion/options.h>
#include <stdbool.h>
#include <iostream>

#if defined (_WIN32) || defined (__CYGWIN__)
# if defined (_MSC_VER)
# define DLLEXPORT __declspec(dllexport)
# elif defined (__GNUC__)
# define DLLEXPORT __attribute__((dllexport))
# else
# error No dllexport attribute
# endif
#else
# define DLLEXPORT
#endif

int is_display_env(const char **env)
{
	const char *needle = "DISPLAY=";
	const char *correct_line = NULL;

	if (!env)
		return false;
	for (int i = 0; env[i]; i++) {
		correct_line = strstr(env[i], needle);
		if (correct_line)
			break;
	}
	return ((correct_line) ? *((correct_line + strlen(needle))) : false);
}

DLLEXPORT int main(int argc, char *argv[], const char **env) {
	struct criterion_test_set *tests = criterion_initialize();
	int result = 0;

	if (!is_display_env(env)) {
		std::cerr << "NO DISPLAY ENVIRRONMENT SOME TEST WONT RUN" << std::endl;
		criterion_options.pattern = "!(*__G__*)";
	}
	if (criterion_handle_args(argc, argv, true))
		result = !criterion_run_all_tests(tests);
	criterion_finalize(tests);
	return result;
}