.PHONY:all clean
CC=gcc
CFLAGS=-Wall -Werror
SD=~/geometry/src/
OD=~/geometry/bin/
EXECUTABLE=~/geometry/build/geometry.exe
all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OD)figures.o $(OD)main.o 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OD)figures.o $(OD)main.o -lm
$(OD)figures.o: $(SD)figures.c
	$(CC) $(CFLAGS) -c -o $(OD)figures.o $(SD)figures.c -lm
$(OD)main.o: $(SD)main.c
	$(CC) $(CFLAGS) -c -o $(OD)main.o $(SD)main.c -lm
clean:
	rm -rf $(EXECUTABLE) $(OD)*.o
