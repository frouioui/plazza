##
## Plazza
##
## Makefile of the configuration_reader static library
##

# Compilation
CXX			=	g++
CXXFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY) -std=c++14

LIBRARY_NAME	=	libconfig_reader.a
TEST_NAME		=	config_reader_test

OBJS		=	$(SRC:.cpp=.o)
TEST_OBJS	=	$(TEST_SRC:.cpp=.o)

CRITERION	=	-lcriterion -lgcov --coverage

# Paths
SRC_DIRECTORY		=	./src
TEST_DIRECTORY		=	./tests
INCLUDE_DIRECTORY	=	./include

# Source files
SRC				=	$(SRC_DIRECTORY)/ConfigReader.cpp				\
					$(SRC_DIRECTORY)/ConfigReaderError.cpp			\

# Test files
TEST_SRC		=	$(TEST_DIRECTORY)/ConfigReaderTests.cpp			\

# Rules
all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJS)
	ar rc $(LIBRARY_NAME) $(OBJS)
	ar t $(LIBRARY_NAME)

tests_compile:
	$(CXX) $(SRC) $(TEST_SRC) -o $(TEST_NAME) $(CRITERION) -I$(INCLUDE_DIRECTORY)

tests_run:
	./$(TEST_NAME) -j1 --full-stats

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.conf

fclean: clean
	rm -f $(LIBRARY_NAME) $(TEST_NAME)

re: fclean all
