CFLAGS       = -std=c11 -Wall -Wpedantic -Werror -pedantic-errors -g -pthread
LDFLAGS      =
LIBS         =
SOURCES      = list.c main.c
OBJECTS      = $(SOURCES:.c=.o)
NAME    	 = output
VALGRIND_LOG = valgrind_$(NAME).log

.PHONY: memcheck

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) $(LIBS)

$(OBJECTS):
	$(CC) -c $(CFLAGS) $(SOURCES)

rebuild: clean $(NAME)

build-run: clean $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)
	rm -f valgrind*
	rm -f *.o

memcheck:
	valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --verbose \
             --log-file=$(VALGRIND_LOG) \
             ./$(NAME)