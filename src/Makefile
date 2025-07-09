CC = gcc
CFLAGS += -g -Wall -Wextra -Werror -I../lib
LDLIBS += -llinkedlist
LDFLAGS += -L../lib -Wl,-rpath,${shell realpath ../lib}

SRC_DIRS := .
BUILD_DIR := ../build/src

SRCS := ${shell find $(SRC_DIRS) -name '*.c'}
OBJS := ${SRCS:%=$(BUILD_DIR)/%.o}

.PHONY: all clean

all: $(OBJS) address_book

address_book:
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD_DIR)/%.c.o: %.c
	@if [ ! -d $(dir $@) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR) address_book