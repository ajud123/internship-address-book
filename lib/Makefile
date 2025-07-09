CC = gcc
CFLAGS += -g -Wall -Werror -Wextra

SRC_DIRS := .
BUILD_DIR := ../build/lib

SRCS := ${shell find $(SRC_DIRS) -name '*.c'}
OBJS := ${SRCS:%=$(BUILD_DIR)/%.o}

.PHONY: all clean

all: $(OBJS) liblinkedlist.so

liblinkedlist.so: $(OBJS)
	$(CC) $(OBJS) -shared -o $@

$(BUILD_DIR)/%.c.o: %.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CPPFLAGS) $(CFLAGS) -fPIC -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR) liblinkedlist.so