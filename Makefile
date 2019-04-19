##
## EPITECH PROJECT, 2019
## plazza
## File description:
## Makefile
##

# PROJECT

plazza.name			=	plazza

plazza.srcs			=	src/Kitchen/Kitchen.cpp			\
						src/reception/Error.cpp			\
						src/reception/Reception.cpp		\
						src/reception/Shell.cpp			\
						src/Kitchen/Cook.cpp			\
						src/Kitchen/Stock.cpp			\

plazza.main 		=	src/main.cpp

plazza.objs		=	$(addprefix $(dir $(BUILD_DIR)$(plazza.name)/), $(plazza.srcs:.cpp=.o))	\
					$(addprefix $(dir $(BUILD_DIR)$(plazza.name)/), $(plazza.main:.cpp=.o))

plazza.cxxflags		=	-Werror

plazza.ldflags		=

# LIBS

LIBS				=	lib/logger/liblogger.a							\
						lib/configuration_reader/libconfig_reader.a		\

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

all: $(plazza.name)

#	MANDATORY

define LIB_RULES =
$(1):
	make -C $$(dir $$@)
HEADERS += -I $$(dir $(1))include
LDFLAGS += -L $$(dir $(1)) -l $$(subst lib,,$$(notdir $$(basename $(1))))

$(1)_fclean:
	make fclean -C $$(dir $$@)
LIB_FCLEAN += $(1)_fclean

$(1)_tests_compile:
	make tests_compile -C $$(dir $$@)
LIB_TEST_COMPILE += $(1)_tests_compile

$(1)_tests_run:
	make tests_run -C $$(dir $$@)
LIB_TESTS_RUN += $(1)_tests_run

endef

$(foreach lib,$(LIBS),$(eval $(call LIB_RULES,$(lib))))

$(plazza.name): $(LIBS)	$(plazza.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(plazza.cxxflags) $(plazza.ldflags)

$(unit_tests.name): $(LIBS) $(unit_tests.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(unit_tests.cxxflags) $(unit_tests.ldflags)

tests_compile: $(LIB_TEST_COMPILE) $(unit_tests.name)

tests_run: tests_compile $(LIB_TESTS_RUN)
	./$(unit_tests.name) -j1 --verbose --full-stats

clean:
	rm -rf $(BUILD_DIR)

fclean:	clean $(LIB_FCLEAN)
	rm -rf $(plazza.name) $(debug.name) $(unit_tests.name) $(DOCS_DIR)

re: fclean all

# Create .o

$(BUILD_DIR)$(plazza.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(plazza.cxxflags) $< -c -o $@

$(BUILD_DIR)$(debug.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(debug.cxxflags) $< -c -o $@

$(BUILD_DIR)$(unit_tests.name)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(unit_tests.cxxflags) $< -c -o $@

# Develloper tools
$(debug.name): $(LIBS) $(debug.objs)
	$(CXX) -o $@ $^ $(LDFLAGS) $(CXXFLAGS) $(debug.cxxflags) $(debug.ldflags)

debug: $(debug.name)

# DOCS
docs:
	doxygen $(DOXYFILE)

.PHONY: docs

cleanDocs:
	rm -rf $(DOCS_DIR)