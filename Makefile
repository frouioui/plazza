##
## EPITECH PROJECT, 2019
## plazza
## File description:
## Makefile
##

# PROJECT

plazza.name			=	plazza

plazza.srcs			=	src/reception/Error.cpp			\
						src/reception/Reception.cpp		\

plazza.main 		=	src/main.cpp

plazza.cxxflags		=	-Werror

plazza.ldflags		=

# DOCS

DOCS_DIR			=	docs/

DOXYFILE			=	Plazza

# TESTS

unit_tests.name		=	unit_tests_$(plazza.name)

unit_tests.srcs		=	$(plazza.srcs)	\

unit_tests.main 	=	tests/criterion_main.cpp

unit_tests.cxxflags	=	-fprofile-arcs -ftest-coverage

unit_tests.ldflags	=	-lcriterion -lgcov

# DEBUG

debug.name			=	debug_$(plazza.name)

debug.srcs			=	$(plazza.srcs)

debug.main 			=	$(plazza.main)

debug.cxxflags		=	-g3

debug.ldflags		=

# COMPILATION

BUILD_DIR			=	build/

HEADERS				=	-I ./include

CXXFLAGS			=	-Wall -Wextra -std=c++14 $(HEADERS)

LDFLAGS				=

define COMPILE_template =

POBJS					=	$(addprefix $(dir $(BUILD_DIR)$(1)/), $$($(1).srcs:.cpp=.o))	\
							$(addprefix $(dir $(BUILD_DIR)$(1)/), $$($(1).main:.cpp=.o))

$(BUILD_DIR)$(1)/%.o: %.cpp
	@mkdir -p $$(dir $$@)
	$(CXX) $(CXXFLAGS) $$($(1).cxxflags) $$< -c -o $$@

endef

#	MANDATORY

all: $(plazza.name)

$(plazza.name):	$(eval $(call COMPILE_template,plazza)) $(POBJS)
	$(CXX) -o $(plazza.name) $^ $(LDFLAGS) $(CXXFLAGS) $(plazza.cxxflags) $(plazza.ldflags)

$(unit_tests.name):	$(eval $(call COMPILE_template,unit_tests)) $(POBJS)
	$(CXX) -o $(unit_tests.name) $^ $(LDFLAGS) $(CXXFLAGS) $(unit_tests.cxxflags) $(unit_tests.ldflags)

tests_compile: $(unit_tests.name)

tests_run: $(unit_tests.name)
	./$(unit_tests.name) -j1 --verbose --full-stats

clean:
	rm -rf $(BUILD_DIR)

fclean:	clean
	rm -rf $(plazza.name) $(debug.name) $(unit_tests.name) $(DOCS_DIR)

re: fclean all

# Develloper tools
debug:	$(eval $(call COMPILE_template,debug)) $(POBJS)
	$(CXX) -o $(debug.name) $^ $(LDFLAGS) $(CXXFLAGS) $(debug.cxxflags) $(debug.ldflags)

# DOCS
docs:
	doxygen $(DOXYFILE)

.PHONY: docs

cleanDocs:
	rm -rf $(DOCS_DIR)