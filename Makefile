CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pthread -fsanitize=thread -g
LDFLAGS = -fsanitize=thread
# CFLAGS = -Wall -Wextra -std=c11

SRCS = futex.c mutex.c chan.c main.c
OBJS = $(SRCS:.c=.o)
HEADERS = futex.h mutex.h chan.HEADERS

TARGET = channel_test

.PHONY: all clean

all: $(TARGET)

# $(TARGET): $(OBJS)
# 	$(CC) $(CFLAGS) $^ -o $@
$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)