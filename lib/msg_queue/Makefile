##
## Plazza
##
## Makefile of the msg_queue static library
##

# Compilation
CXX			=	g++ -g3
CXXFLAGS	=	-W -Werror -Wextra -Wall -I$(INCLUDE_DIRECTORY) -std=c++14

LIBRARY_NAME	=	libmsg_queue.a
TEST_NAME		=	msg_queue_test

OBJS		=	$(SRC:.cpp=.o)
TEST_OBJS	=	$(TEST_SRC:.cpp=.o)

CRITERION	=	-lcriterion -lgcov --coverage

# Paths
SRC_DIRECTORY		=	./src
TEST_DIRECTORY		=	./tests
INCLUDE_DIRECTORY	=	./include

# Source files
SRC				=	$(SRC_DIRECTORY)/MessageQueue.cpp					\
					$(SRC_DIRECTORY)/MessageQueueError.cpp				\

# Test files
TEST_SRC		=	$(TEST_DIRECTORY)/MessageQueueTests.cpp				\
					$(TEST_DIRECTORY)/MessageQueueFailedReadTests.cpp	\
					$(TEST_DIRECTORY)/MessageQueueSuccessReadTests.cpp	\

# Rules
all: $(LIBRARY_NAME)

$(LIBRARY_NAME): $(OBJS)
	ar rc $(LIBRARY_NAME) $(OBJS)
	ar t $(LIBRARY_NAME)

tests_compile:
	$(CXX) $(SRC) $(TEST_SRC) -o $(TEST_NAME) $(CRITERION) -I$(INCLUDE_DIRECTORY)

tests_run: tests_compile
	./$(TEST_NAME) -j1 --full-stats --verbose --xml=../../report/message_queue.xml

clean:
	rm -f $(OBJS) $(TEST_OBJS)
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.conf

fclean: clean
	rm -f $(LIBRARY_NAME) $(TEST_NAME)

re: fclean all