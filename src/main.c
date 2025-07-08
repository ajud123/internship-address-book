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
		else                                                                                         \
			buf[len - 1] = '\0';                                                                 \
	} while (0)

int parse_input(struct Address **addrBook, char *input);
int perform_search(struct Address **addrBook);

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
		printf("5) Delete the entire address book.\n");
		printf("6) Find address by index.\n");
		printf("7) Find address by name, surname, email or phone number.\n");
		printf("X) Exit.\n");

		char input[20];
		// Large buffer used so we don't read 1 char
		// from stdin and then use what's left in the other prompts.
		fgets(input, 20, stdin);
		if (strlen(input) > 2)
			printf("Unknown command. ");

		int status = parse_input(&book, input);
		if (status == 1) {
			if (book != NULL)
				delete_list(&book);
			return 0;
		}
		printf("Press enter key to continue.");
		if (fgets(input, 20, stdin) == NULL) {
			if (book != NULL)
				delete_list(&book);
			return 0;
		}
	}
	if (book != NULL)
		delete_list(&book);
	return 0;
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
		if (remove_at_list_index(addrBook, index) == 0) {
			printf("Deleted element at index %i\n", index);
			dump_address_book(*addrBook);
		} else {
			printf("No address at index %i\n", index);
		}

		// }
		break;
	}
	case '5': {
		printf("Are you sure you want to do this? This cannot be undone.\n");
		char confirm[30];
		int status = 2;
		while (status > 1) {
			READ_INPUT("(y/n): ", confirm);
			status = parse_yes_no(confirm);
		}
		if (!status) {
			delete_list(addrBook);
			printf("List cleared.\n");
			dump_address_book(*addrBook);
		} else {
			printf("Operation aborted.\n");
		}
		break;
	}
	case '6': {
		char position[30];
		READ_INPUT("Enter the index of the address you wish to see: ", position);
		int index = atoi(position);
		struct Address *address;
		get_address_at_index(addrBook, &address, index);
		if (address != NULL)
			print_single_address(address);
		else
			printf("Could not find an address at index %i.\n", index);
		break;
	}
	case '7': {
		perform_search(addrBook);
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

int perform_search(struct Address **book)
{
        char field[30];
        printf("Available fields to search by:\n");
        printf("1) Name\n");
        printf("2) Surname\n");
        printf("3) Email\n");
        printf("4) Phone number\n");
        int hasField = 0;
        while(!hasField){
                READ_INPUT("Enter the field number by which you want to search by: ", field);
                if(strlen(field) > 2) {
                        printf("Unknown value. Try again\n");
                        continue;
                }
                switch(field[0]){
                case '1':
                        hasField = 1;
                        break;
                case '2':
                        hasField = 2;
                        break;
                case '3':
                        hasField = 3;
                        break;
                case '4':
                        hasField = 4;
                        break;
                default:
                        printf("Unknown value. Try again\n");
                        break;
                }
        }
        char value[30];
        READ_INPUT("Enter the field value: ", value);
        struct Address *element = NULL;
        int i = get_address_by_value(book, &element, (enum SearchField)hasField, value);
        if(i > 0){
                printf("%i) ", i);
                print_single_address(element);
        } else {
                printf("Requested address not found. \n");
        }
        return 0;
}