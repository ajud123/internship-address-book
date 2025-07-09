CC = gcc
CFLAGS += -g -Wall -Wextra -Werror -I../lib -I../src
LDLIBS += -llinkedlist
LDFLAGS += -L../

SRC_DIRS := .
BUILD_DIR := ../build/src

SRCS := ${shell find $(SRC_DIRS) -name '*.c'}
OBJS := ${SRCS:%=$(BUILD_DIR)/%.o}

.PHONY: all clean

all: $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR)