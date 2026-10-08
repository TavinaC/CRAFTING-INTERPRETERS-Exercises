CC = gcc
CFLAGS = -std=c99
TARGET = clox
SRCS = main.c chunk.c debug.c memory.c value.c vm.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(TARGET) $(OBJS)
.PHONY: all clean