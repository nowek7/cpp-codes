CFLAGS  = -Wall -Werror -Wpedantic -g
LDFLAGS =
LIBS    =
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
NAME    = backup

.SILENT: run clean help read-files read

all: $(NAME)

build: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) $(LIBS)

$(OBJECTS):
	$(CC) -c $(CFLAGS) $(SOURCES)

rebuild: clean $(NAME)

run: rebuild
	./$(NAME) $(src) $(dest)

clean:
	rm -f $(OBJECTS)
	rm -f $(NAME)

help:
	echo "make                                       -> Build program   "
	echo "make build                                 -> Build program   "
	echo "make rebuild                               -> Rebuild program "
	echo "make run                                   -> Run program     "
	echo "make clean                                 -> Clean build     "
	echo "make read-file src=src_path dest=dest_path -> Read files      "
	echo "make read-file file=file_path              -> Read file       "

read-files:
	echo "---------$(src)---------" cat $(src)
	echo "---------$(dest)---------" cat $(dest)

read:
	cat $(file)
