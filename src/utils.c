#include "linkedlist.h"
#include <stdio.h>

struct Address *read_address_book(char *filename)
{
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		return NULL;
	}
	struct Address *book;
	char line[30 * 4];
	while (fgets(line, 30 * 4, f) != NULL) {
		struct Address *address = create_address_from_line(line);
		if (address != NULL) {
			add_to_list(&book, address);
		} else {
			perror("Failed to read address from address book.");
		}
	}
	return book;
}

void print_address_book(struct Address *book)
{
	if (book == NULL) {
		printf("The phone book is empty.\n");
	}
        int i = 1;
	while (book != NULL) {
		printf("%i. %s %s:\n", i, book->name, book->surname);
		printf("* Email: %s\n", book->email);
		printf("* Phone: %s\n", book->phone);
		printf("\n");
		book = book->next;
                i++;
	}
}