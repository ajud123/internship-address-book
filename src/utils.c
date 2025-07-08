#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Address *read_address_book()
{
        char filename[256];
	strncpy(filename, getenv("HOME"), 256);
	strncat(filename, "/addresses.csv", 15);
	FILE *f = fopen(filename, "r");
	if (f == NULL) {
		return NULL;
	}
	struct Address *book = NULL;
	char line[30 * 4];
	while (fgets(line, sizeof(line), f) != NULL) {
                if(strcmp(line, "\n") == 0)
                        continue;
		struct Address *address = create_address_from_line(line);
		if (address != NULL) {
			add_to_list(&book, address);
		} else {
			perror("Failed to read address from address book.");
                        return NULL;
		}
	}
        fclose(f);
	return book;
}

void print_single_address(struct Address *address){
        printf("%s %s:\n", address->name, address->surname);
        printf("* Email: %s\n", address->email);
        printf("* Phone: %s\n", address->phone);
        printf("\n");
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

/*
 * Returns 0 if it succeeds writing the address book to disk.
 * Returns 1 if it fails to open the address book for writing.
 * Returns 2 if writing to the address book fails.
 */
int dump_address_book(struct Address *book)
{
        char filename[256];
	strncpy(filename, getenv("HOME"), 256);
	strncat(filename, "/addresses.csv", 15);
	FILE *f = fopen(filename, "w");
        if(f == NULL)
                return 1;
        while (book != NULL) {
		if(fprintf(f, "%s,%s,%s,%s\n", book->name, book->surname, book->email, book->phone) < 0){
                        perror("Failed to write to address book file");
                        if(fclose(f) == EOF) {
                                perror("FATAL: Failed to close address book file descriptor");
                                abort();
                        }
                        return 2;
                }
		book = book->next;
	}
        fclose(f);
        return 0;
}

/*
 * Returns 2 if the input is not "y" or "n" or any other capitalized variation
 * Returns 0 if the input is "y" or "Y"
 * Returns 1 if the input is "n" or "N"
 */
int parse_yes_no(char *input){
        if(strlen(input) > 2)
                return 2;
        switch(input[0]){
                case 'Y':
                case 'y':
                        return 0;
                case 'N':
                case 'n':
                        return 1;
        }
        return 2;
}