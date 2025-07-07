#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "utils.h"

#define READ_INPUT(msg, buf)                                                                                 \
	do {                                                                                                 \
		printf(msg);                                                                                 \
		fgets(buf, sizeof(buf), stdin);                                                              \
		int len = strlen(buf);                                                                       \
		if (len == 1)                                                                                \
			buf[len - 1] = '-';                                                                  \
	} while (0)

int parse_input(struct Address **addrBook, char *input);

int main()
{
	struct Address *book;
	book = read_address_book();
	while (1) {
		printf("\033c");
		printf("Select the desired action:\n");
		printf("1) Display all records in the address book.\n");
		printf("2) Add a new address to the book (at the end).\n");
		printf("3) Insert a new address to the book at a position.\n");
		printf("4) Delete an address from the book at a position.\n");
		printf("X) Exit.\n");

		char input[20];
		// Large buffer used so we don't read 1 char
		// from stdin and then use what's left in the other prompts.
		fgets(input, 20, stdin);
		if (strlen(input) > 2)
			printf("Unknown command. ");

		int status = parse_input(&book, input);
		if (status == 1)
			return 0;
		printf("Press enter key to continue.");
		if (fgets(input, 20, stdin) == NULL)
			return 0;
	}
	return 0;
}

void handle_deletion()
{
}

/*
 * The method takes in the given input and determines what to do with it.
 * Returns 0 if all execution was handled correctly.
 * Returns 1 if if the given input was to exit.
 */
int parse_input(struct Address **addrBook, char *input)
{
	switch (input[0]) {
	case '1': {
		print_address_book(*addrBook);
		break;
	}
	case '2': {
		char name[30];
		char surname[30];
		char phone[30];
		char email[30];
		READ_INPUT("Enter the name of the person to add: ", name);
		READ_INPUT("Enter the surname of the person to add: ", surname);
		READ_INPUT("Enter the email address of the person to add: ", email);
		READ_INPUT("Enter the phone number of the person to add: ", phone);
		struct Address *newAddr = create_address(name, surname, email, phone);
		if (newAddr == NULL) {
			printf("Could not generate a new address from the given data. \n");
		} else {
			add_to_list(addrBook, newAddr);
			dump_address_book(*addrBook);
		}
		break;
	}
	case '3': {
		char position[30];
		READ_INPUT("Enter the index where to put the new address: ", position);
		int i = atoi(position);

		char name[30];
		char surname[30];
		char phone[30];
		char email[30];
		READ_INPUT("Enter the name of the person to add: ", name);
		READ_INPUT("Enter the surname of the person to add: ", surname);
		READ_INPUT("Enter the email address of the person to add: ", email);
		READ_INPUT("Enter the phone number of the person to add: ", phone);
		struct Address *newAddr = create_address(name, surname, email, phone);
		if (newAddr == NULL) {
			printf("Could not generate a new address from the given data. \n");
		} else {
			insert_in_list_index(addrBook, newAddr, i);
			dump_address_book(*addrBook);
		}
		break;
	}
	case '4': {
		char position[30];
                READ_INPUT("Enter the index of the address to delete: ", position);
                int index = atoi(position);
                struct Address *foundElement;
                int status = get_address_at_index(addrBook, &foundElement, index);
                if (foundElement == NULL) {
                        printf("No address at index %i\n", index);
                } else {
                        /* deletion call */
                        printf("Deleted element at index %i");
                }
		break;
	}
	case 'x':
	case 'X':
		return 1;
	default:
		break;
	}
	return 0;
}