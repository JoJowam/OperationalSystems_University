CC=g++
CFLAGS=-std=c++17 -Wall -Wextra
EXEC=../TP03/main

BIN_DIR=bin
SRC_DIR=SRC

OBJS=$(BIN_DIR)/main.o $(BIN_DIR)/produtor.o $(BIN_DIR)/consumidor.o $(BIN_DIR)/buffer.o

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

$(BIN_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main.o

$(BIN_DIR)/produtor.o: $(SRC_DIR)/produtor.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/produtor.cpp -o $(BIN_DIR)/produtor.o

$(BIN_DIR)/consumidor.o: $(SRC_DIR)/consumidor.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/consumidor.cpp -o $(BIN_DIR)/consumidor.o

$(BIN_DIR)/buffer.o: $(SRC_DIR)/buffer.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/buffer.cpp -o $(BIN_DIR)/buffer.o

clean:
	rm -rf $(EXEC) $(BIN_DIR)/*.o
