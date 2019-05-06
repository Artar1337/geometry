.PHONY:all clean test
CC = gcc
CFLAGS = -Wall -Werror
SD = src/
OD = build/
TD = test/
TEST = bin/test.exe
EXECUTABLE = bin/geometry.exe
all: $(EXECUTABLE)
	
test: $(TEST)
	
$(EXECUTABLE): $(OD)main.o $(OD)figures.o $(OD)intersects.o
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OD)main.o $(OD)figures.o $(OD)intersects.o -lm
$(OD)main.o: $(SD)main.c
	$(CC) $(CFLAGS) -c -o $(OD)main.o $(SD)main.c -lm
$(OD)figures.o: $(SD)figures.c
	$(CC) $(CFLAGS) -c -o $(OD)figures.o $(SD)figures.c -lm
$(OD)intersects.o: $(SD)intersects.c
	$(CC) $(CFLAGS) -c -o $(OD)intersects.o $(SD)intersects.c -lm
$(TEST): $(OD)test.o $(OD)tests.o
	$(CC) $(CFLAGS) -std=c99 -I thirdparty -I src -o $(TEST) $(OD)test.o $(OD)tests.o -lm
$(OD)tests.o: $(TD)tests.c
	$(CC) $(CFLAGS) -std=c99 -I thirdparty -I src -c -o $(OD)tests.o $(TD)tests.c -lm
$(OD)test.o: $(TD)test.c
	$(CC) $(CFLAGS) -std=c99 -I thirdparty -I src -c -o $(OD)test.o $(TD)test.c -lm
clean:
	rm -rf $(EXECUTABLE) $(TEST) $(OD)*.o
