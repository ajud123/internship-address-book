CC = gcc
CFLAGS += -g -Wall -Wextra -Werror

SRC_DIRS := ./src
BUILD_DIR := ./build

SRCS := ${shell find $(SRC_DIRS) -name '*.c'}
OBJS := ${SRCS:%=$(BUILD_DIR)/%.o}

.PHONY: all clean

address_book: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

all: address_book $(OBJS)

$(BUILD_DIR)/%.c.o: %.c
	@if [ ! -d $(BUILD_DIR) ]; then mkdir -p $(dir $@); fi
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BUILD_DIR) address_book