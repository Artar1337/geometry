.PHONY:all clean
CC = gcc
CFLAGS = -Wall -Werror
SD = src/
OD = build/
EXECUTABLE = bin/geometry.exe
all: $(EXECUTABLE)
	
$(EXECUTABLE): $(OD)main.o $(OD)figures.o $(OD)intersects.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OD)main.o $(OD)figures.o $(OD)intersects.o -lm
$(OD)main.o: $(SD)main.c
	$(CC) $(CFLAGS) -c -o $(OD)main.o $(SD)main.c -lm
$(OD)figures.o: $(SD)figures.c
	$(CC) $(CFLAGS) -c -o $(OD)figures.o $(SD)figures.c -lm
$(OD)intersects.o: $(SD)intersects.c
	$(CC) $(CFLAGS) -c -o $(OD)intersects.o $(SD)intersects.c -lm
clean:
	rm -rf $(EXECUTABLE) $(OD)*.o
