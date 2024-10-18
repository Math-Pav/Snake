CC = gcc
CFLAGS = -Wall -g -I src
LDFLAGS = -lSDL2 -lSDL2_ttf
TARGET = snake

SRC_DIR = src

SRCS = $(SRC_DIR)/main.c $(SRC_DIR)/game.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o $(TARGET)
