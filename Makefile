CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lncurses

TARGET = encrypt_app
SRC = encrypt_app.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
