##
## EPITECH PROJECT, 2019
## plazza
## File description:
## Makefile
##

# PROJECT

plazza.name			=	plazza

plazza.srcs			=	src/Plazza.cpp

plazza.main 		=	src/main.cpp

plazza.objs		=	$(addprefix $(dir $(BUILD_DIR)$(plazza.name)/), $(plazza.srcs:.cpp=.o))	\
					$(addprefix $(dir $(BUILD_DIR)$(plazza.name)/), $(plazza.main:.cpp=.o))

plazza.cxxflags		=	-Werror

plazza.ldflags		=

# DOCS

DOCS_DIR			=	docs/

DOXYFILE			=	Plazza

# TESTS

unit_tests.name		=	unit_tests_$(plazza.name)

unit_tests.srcs		=	$(plazza.srcs)	\

unit_tests.main 	=	tests/criterion_main.cpp

unit_tests.objs		=	$(addprefix $(dir $(BUILD_DIR)$(unit_tests.name)/), $(unit_tests.srcs:.cpp=.o))	\
						$(addprefix $(dir $(BUILD_DIR)$(unit_tests.name)/), $(unit_tests.main:.cpp=.o))

unit_tests.cxxflags	=	-fprofile-arcs -ftest-coverage

unit_tests.ldflags	=	-lcriterion -lgcov

# DEBUG

debug.name			=	debug_$(plazza.name)

debug.srcs			=	$(plazza.srcs)

debug.objs			=	$(addprefix $(dir $(BUILD_DIR)$(debug.name)/), $(debug.srcs:.cpp=.o))	\
						$(addprefix $(dir $(BUILD_DIR)$(debug.name)/), $(debug.main:.cpp=.o))

debug.main 			=	$(plazza.main)

debug.cxxflags		=	-g3

debug.ldflags		=

# COMPILATION

BUILD_DIR			=	build/

HEADERS				=	-I ./include

CXXFLAGS			=	-Wall -Wextra -std=c++14 $(HEADERS)

LDFLAGS				=


$(BUILD_DIR)$(plazza.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(plazza.cxxflags) $< -c -o $@

$(BUILD_DIR)$(debug.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(debug.cxxflags) $< -c -o $@

$(BUILD_DIR)$(unit_tests.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(unit_tests.cxxflags) $< -c -o $@

#	MANDATORY

all: $(plazza.name)

$(plazza.name):	$(plazza.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(plazza.cxxflags) $(plazza.ldflags)

$(unit_tests.name): $(unit_tests.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(unit_tests.cxxflags) $(unit_tests.ldflags)

tests_compile: $(unit_tests.name)

tests_run: $(unit_tests.name)
	./$(unit_tests.name) -j1 --verbose --full-stats

clean:
	rm -rf $(BUILD_DIR)

fclean:	clean
	rm -rf $(plazza.name) $(debug.name) $(unit_tests.name) $(DOCS_DIR)

re: fclean all

# Develloper tools
$(debug.name): $(debug.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(debug.cxxflags) $(debug.ldflags)

debug: $(debug.name)

# DOCS
docs:
	doxygen $(DOXYFILE)

.PHONY: docs

cleanDocs:
	rm -rf $(DOCS_DIR)