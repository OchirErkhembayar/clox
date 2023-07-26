CC=gcc
CFLAGS=-Wall -Wextra -pedantic -std=c2x

TARGET = clox
SRCS = main.c chunk.c memory.c debug.c value.c vm.c scanner.c compiler.c object.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
