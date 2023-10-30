CC = gcc
CFLAGS = -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

BIN = bin/
SRC = src/
OBJS = $(BIN)main.o $(BIN)snake.o
PROJECT_NAME = snasket

all : $(PROJECT_NAME) clean 

$(PROJECT_NAME) : $(OBJS)
	$(CC) -o $(BIN)$(PROJECT_NAME) $(OBJS) $(CFLAGS) 

$(BIN)main.o : $(SRC)main.c
	$(CC) -c -o $(BIN)main.o $(SRC)main.c  $(CFLAGS)


$(BIN)snake.o : $(SRC)snskt/snake.c
	$(CC) -c -o $(BIN)snake.o $(SRC)snskt/snake.c  $(CFLAGS)



.PHONY : clean
clean : 
	rm -f $(BIN)*.o
