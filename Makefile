CC = clang
CFLAGS = -Wall -O2
SRC = src
OBJ = obj

all: prog

$(OBJ):
	mkdir $@

$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

prog: $(OBJ)/file_reader.o $(OBJ)/key_cracker.o $(OBJ)/decryption.o $(SRC)/main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ)/* prog