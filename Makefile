CC = g++
CFLAGS = -Iinclude -Llib -O3 -lraylib -lopengl32 -lgdi32 -lwinmm  -llibpd -lportaudio -mwindows -fpermissive 

BIN = bin/
SRC = src/
OBJS = $(BIN)main.o $(BIN)snake.o $(BIN)menu.o 
PROJECT_NAME = snasket

all : $(PROJECT_NAME) clean 

$(PROJECT_NAME) : $(OBJS)
	$(CC) -o $(BIN)$(PROJECT_NAME) $(OBJS) $(CFLAGS) 

$(BIN)main.o : $(SRC)main.cpp
	$(CC) -c -o $(BIN)main.o $(SRC)main.cpp $(CFLAGS)


$(BIN)snake.o : $(SRC)snskt/snake.cpp
	$(CC) -c -o $(BIN)snake.o $(SRC)snskt/snake.cpp $(CFLAGS)
	
$(BIN)menu.o : $(SRC)snskt/menu.cpp
	$(CC) -c -o $(BIN)menu.o $(SRC)snskt/menu.cpp $(CFLAGS)




.PHONY : clean
clean : 
	rm -f $(BIN)*.o
