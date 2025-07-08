#include "options.h"
#include "constants.h"
#include "utils.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void display_all(struct Address **addrBook)
{
	print_address_book(*addrBook);
}

static void add_to_end(struct Address **addrBook)
{
	char name[NAME_LEN];
	char surname[SURNAME_LEN];
	char phone[PHONE_LEN];
	char email[EMAIL_LEN];
	read_input("Enter the name of the person to add: ", name, NAME_LEN);
	read_input("Enter the surname of the person to add: ", surname, SURNAME_LEN);
	read_input("Enter the email address of the person to add: ", email, EMAIL_LEN);
	read_input("Enter the phone number of the person to add: ", phone, PHONE_LEN);
	struct Address *newAddr = create_address(name, surname, email, phone);
	if (newAddr == NULL) {
		printf("Could not generate a new address from the given data. \n");
	} else {
		add_to_list(addrBook, newAddr);
		dump_address_book(*addrBook);
	}
}

static void insert_at_index(struct Address **addrBook)
{
	char position[OPTIONS_INPUT_LEN];
	read_input("Enter the index where to put the new address: ", position, sizeof(position));
	int i = atoi(position);

	char name[NAME_LEN];
	char surname[SURNAME_LEN];
	char phone[PHONE_LEN];
	char email[EMAIL_LEN];
	read_input("Enter the name of the person to add: ", name, NAME_LEN);
	read_input("Enter the surname of the person to add: ", surname, SURNAME_LEN);
	read_input("Enter the email address of the person to add: ", email, EMAIL_LEN);
	read_input("Enter the phone number of the person to add: ", phone, PHONE_LEN);
	struct Address *newAddr = create_address(name, surname, email, phone);
	if (newAddr == NULL) {
		printf("Could not generate a new address from the given data. \n");
	} else {
		insert_in_list_index(addrBook, newAddr, i);
		dump_address_book(*addrBook);
	}
}

static void delete_at_index(struct Address **addrBook)
{
	char position[OPTIONS_INPUT_LEN];
	read_input("Enter the index of the address to delete: ", position, sizeof(position));
	int index = atoi(position);
	if (remove_at_list_index(addrBook, index) == 0) {
		printf("Deleted element at index %i\n", index);
		dump_address_book(*addrBook);
	} else {
		printf("No address at index %i\n", index);
	}
}

static void delete_all(struct Address **addrBook)
{
	printf("Are you sure you want to do this? This cannot be undone.\n");
	char confirm[OPTIONS_INPUT_LEN];
	int status = 2;
	while (status > 1) {
		read_input("(y/n): ", confirm, sizeof(confirm));
		status = parse_yes_no(confirm);
	}
	if (!status) {
		delete_list(addrBook);
		printf("List cleared.\n");
		dump_address_book(*addrBook);
	} else {
		printf("Operation aborted.\n");
	}
}

static void find_by_index(struct Address **addrBook)
{
	char position[OPTIONS_INPUT_LEN];
	read_input("Enter the index of the address you wish to see: ", position, sizeof(position));
	int index = atoi(position);
	struct Address *address;
	get_address_at_index(addrBook, &address, index);
	if (address != NULL)
		print_single_address(address);
	else
		printf("Could not find an address at index %i.\n", index);
}

static void find_by_field_value(struct Address **addrBook)
{
	char field[OPTIONS_INPUT_LEN];
	printf("Available fields to search by:\n");
	printf("1) Name\n");
	printf("2) Surname\n");
	printf("3) Email\n");
	printf("4) Phone number\n");
	int hasField = 0;
	while (!hasField) {
		read_input("Enter the field number by which you want to search by: ", field, sizeof(field));
		if (strlen(field) > 2) {
			printf("Unknown value. Try again\n");
			continue;
		}
		switch (field[0]) {
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
	read_input("Enter the field value: ", value, sizeof(value));
	struct Address *elements = get_addresses_by_value(addrBook, (enum SearchField)hasField, value);
	if (elements != NULL) {
		print_address_book(elements);
	} else {
		printf("Requested address not found. \n");
	}
}

/*
 * The method takes in the given input and determines what to do with it.
 * Returns 0 if all execution was handled correctly.
 * Returns 1 if if the given input was to exit.
 */
extern int parse_input(struct Address **addrBook, char *input)
{
	switch (input[0]) {
	case '1':
		display_all(addrBook);
		break;
	case '2':
		add_to_end(addrBook);
		break;
	case '3':
		insert_at_index(addrBook);
		break;
	case '4':
		delete_at_index(addrBook);
		break;
	case '5':
		delete_all(addrBook);
		break;
	case '6':
		find_by_index(addrBook);
		break;
	case '7':
		find_by_field_value(addrBook);
		break;
	case 'x':
	case 'X':
		return 1;
	default:
		break;
	}
	return 0;
}