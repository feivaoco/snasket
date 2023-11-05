CC = gcc
CFLAGS = -Iinclude -Llib -O3 -lraylib -lopengl32 -lgdi32 -lwinmm  -llibpd -lportaudio -mwindows

BIN = bin/
SRC = src/
OBJS = $(BIN)main.o $(BIN)snake.o $(BIN)menu.o 
PROJECT_NAME = snasket

all : $(PROJECT_NAME) #clean 

$(PROJECT_NAME) : $(OBJS)
	$(CC) -o $(BIN)$(PROJECT_NAME) $(OBJS) $(CFLAGS) 

$(BIN)main.o : $(SRC)main.c
	$(CC) -c -o $(BIN)main.o $(SRC)main.c $(CFLAGS)


$(BIN)snake.o : $(SRC)snskt/snake.c
	$(CC) -c -o $(BIN)snake.o $(SRC)snskt/snake.c $(CFLAGS)
	
$(BIN)menu.o : $(SRC)snskt/menu.c
	$(CC) -c -o $(BIN)menu.o $(SRC)snskt/menu.c $(CFLAGS)




.PHONY : clean
clean : 
	rm -f $(BIN)*.o
