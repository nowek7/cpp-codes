CC      = g++
CFLAGS  = -std=c++17 -Wall -Wpedantic -g
LDFLAGS =
LIBS    = -lpthread
SOURCES = tftp.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
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