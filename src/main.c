#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#include "utils.h"

#define READ_INPUT(msg, buf)                                                                                 \
	do {                                                                                                 \
		printf(msg);                                                                                 \
		fscanf(stdin, "%[^\n]%*c", buf);                                                             \
	} while (0)

int main()
{
	char filename[256];
	strncpy(filename, getenv("HOME"), 256);
	strncat(filename, "/addresses.csv", 15);
	struct Address *book;
	book = read_address_book(filename);
	while (1) {
		printf("\033c");
		printf("Select the desired action:\n");
		printf("1) Display all records in the address book.\n");
		printf("2) Add a new address to the book (at the end).\n");
		printf("X) Exit.\n");

		char input[20];
		fgets(input, 20, stdin);
		switch (input[0]) {
		case '1':
			print_address_book(book);
			break;
		case '2':
			char name[30];
			char surname[30];
			char phone[30];
			char email[30];
			READ_INPUT("Enter the name of the person to add: ", name);
			READ_INPUT("Enter the surname of the person to add: ", surname);
			READ_INPUT("Enter the email address of the person to add: ", email);
			READ_INPUT("Enter the phone number of the person to add: ", phone);
			struct Address *newAddr = create_address(name, surname, phone, email);
			if (newAddr == NULL)
				printf("Could not generate a new address from the given data. \n");
			else
				add_to_list(&book, newAddr);
			// printf("Enter the name of the person to add: ");
			// fscanf(stdin, "%[^\n]%*c", name);
			// printf("Enter the name of the person to add: ");
			// fscanf(stdin, "%[^\n]%*c", name);
			break;
		case 'x':
		case 'X':
			return 0;
		default:
			break;
		}
		printf("Press any key to continue.");
		fgetc(stdin);
	}
	return 0;
}
