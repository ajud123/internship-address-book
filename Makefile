CC = gcc
CFLAGS += -g -Wall -Wextra -Werror -I./lib
LDLIBS += -llinkedlist
LDFLAGS += -L./

SRC_DIR := ./src
LIB_DIR := ./lib
BUILD_DIR := ./build

SRCS := ${shell find $(SRC_DIR) -name '*.c'}
OBJS := ${SRCS:%=$(BUILD_DIR)/%.o}

LIB_SRCS := ${shell find $(LIB_DIR) -name '*.c'}
LIB_OBJS := ${LIB_SRCS:%=$(BUILD_DIR)/%.o}

.PHONY: install uninstall all clean

all: address_book install liblinkedlist.so $(OBJS)

liblinkedlist.so: $(LIB_OBJS)
	$(CC) $(LIB_OBJS) -shared -o $@ 

install: liblinkedlist.so
	@echo Installing requires sudo permissions
	cp liblinkedlist.so /usr/lib
	chmod 0755 /usr/lib/liblinkedlist.so
	ldconfig

uninstall:
	@echo Uninstalling requires sudo permissions
	rm /usr/lib/liblinkedlist.so
	ldconfig

address_book: liblinkedlist.so $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJS): $(SRCS)
	cd $(SRC_DIR); make

$(LIB_OBJS): $(LIB_SRCS)
	cd $(LIB_DIR); make

clean:
	$(RM) -r $(BUILD_DIR) address_book liblinkedlist.so

test:
	echo $(OBJS)