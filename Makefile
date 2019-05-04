.PHONY:all clean
CC=gcc
CFLAGS=-Wall -Werror
SD=~/geometry/src/
OD=~/geometry/build/
EXECUTABLE=~/geometry/bin/geometry.exe
all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OD)figures.o $(OD)main.o $(OD)intersects.o 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OD)figures.o $(OD)main.o $(OD)intersects.o -lm
$(OD)figures.o: 
	$(CC) $(CFLAGS) -c -o $(OD)figures.o $(SD)figures.c -lm
$(OD)main.o: 
	$(CC) $(CFLAGS) -c -o $(OD)main.o $(SD)main.c -lm
$(OD)intersects.o: 
	$(CC) $(CFLAGS) -c -o $(OD)intersects.o $(SD)intersects.c -lm
clean:
	rm -rf $(EXECUTABLE) $(OD)*.o
