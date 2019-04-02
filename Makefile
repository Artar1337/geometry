CC = gcc
CFLAGS = -Wall -Werror -lm
EXECUTABLE = geom
SOURCES = src/main.c src/figures.c
OBJECTS = $(SOURCES:.c=.o)
all:$(SOURCES) $(EXECUTABLE)
$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@
.c.o:
	$(CC) ${CFLAGS) $< -o $@
clean:
	rm -rf *.o *.exe
