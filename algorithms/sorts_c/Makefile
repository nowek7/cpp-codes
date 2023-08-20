CFLAGS  = -std=c11 -Wall -Wpedantic
LDFLAGS =
LIBS    =
SOURCES = main.c my_sort.c
OBJECTS = $(SOURCES:.c=.o)
NAME    = output

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