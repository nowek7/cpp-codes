CFLAGS  = -std=c11 -Wall -Wpedantic -g
LDFLAGS = -Lfigure
LIBS    = -lfigure -lm
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)
NAME    = figureArea

all: libfigure $(NAME)

libfigure:
	make -C figure

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $(NAME) $(LIBS)

$(OBJECTS):
	$(CC) -c $(CFLAGS) $(SOURCES)

rebuild: clean libfigure $(NAME)

build-run: clean libfigure $(NAME) add-lib
	./$(NAME)

add-lib:
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:figure

clean:
	make clean -C figure
	@rm -f $(OBJECTS)
	@rm -f $(NAME)