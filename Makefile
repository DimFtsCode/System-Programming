CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = mysh
SRC_DIR = src
OBJ_DIR = obj
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/def.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
