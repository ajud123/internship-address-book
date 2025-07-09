SRC_DIR := ./src
LIB_DIR := ./lib
BUILD_DIR := ./build

.PHONY: install uninstall all clean src lib

all: lib src address_book

lib:
	$(MAKE) -C $(LIB_DIR)

src: lib
	$(MAKE) -C $(SRC_DIR)

address_book: lib src
	cp $(SRC_DIR)/address_book ./

install: liblinkedlist.so
	@echo Installing requires sudo permissions
	cp liblinkedlist.so /usr/lib
	chmod 0755 /usr/lib/liblinkedlist.so
	ldconfig

uninstall:
	@echo Uninstalling requires sudo permissions
	rm /usr/lib/liblinkedlist.so
	ldconfig

clean:
	$(MAKE) -C $(SRC_DIR) clean
	$(MAKE) -C $(LIB_DIR) clean
	$(RM) -r $(BUILD_DIR) address_book liblinkedlist.so