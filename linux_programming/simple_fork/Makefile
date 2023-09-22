CFLAGS  = -std=c11 -Wall -Wpedantic -g
LDFLAGS =
LIBS    =
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
NAME    = fork

.SILENT: run clean help

all: $(NAME)
build: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) $(LIBS)

$(OBJECTS):
	$(CC) -c $(CFLAGS) $(SOURCES)

rebuild: clean $(NAME)

run:
	./$(NAME)

rebuild-run: rebuild run

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)

help:
	echo "make                                       -> Build program           "
	echo "make build                                 -> Build program           "
	echo "make rebuild                               -> Rebuild program         "
	echo "make run                                   -> Run program             "
	echo "make rebuild-run                           -> Rebuild and run program "
	echo "make clean                                 -> Clean build             "