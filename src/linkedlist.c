#include "linkedlist.h"
#include <string.h>
#include <stdlib.h>

#define DELIMITER ","

struct Address *create_address_from_line(char *line)
{
	char *name;
	char *surname;
	char *email;
	char *phone;

	name	= strtok(line, DELIMITER);
	surname = strtok(NULL, DELIMITER);
	email	= strtok(NULL, DELIMITER);
	phone	= strtok(NULL, DELIMITER);

	// Ensure we're not leaving trailing whitespace in the phone number
	int phonelen = strlen(phone);
	if (phone[phonelen - 1] == '\n')
		phone[phonelen - 1] = '\0';

	struct Address *addr = create_address(name, surname, email, phone);
	return addr;
}

struct Address *create_address(char *name, char *surname, char *email, char *phone)
{
	struct Address *addr = malloc(sizeof(struct Address));
	addr->next	     = NULL;
	strncpy(addr->name, name, 30);
	strncpy(addr->surname, surname, 30);
	strncpy(addr->email, email, 30);
	strncpy(addr->phone, phone, 30);
	return addr;
}

/*
 * Returns -1 if the element was not found and sets the *address to NULL
 * Returns 0 if the element is found and sets *address to the found element's address
 * Returns 1 if index < 1 and sets *address to NULL
 * Returns 2 if index is more than the amount of items in the linked list and sets *address to NULL
 * Returns 3 if anything else happens and sets *address to NULL.
 */
int get_address_at_index(struct Address **list, struct Address **address, int index)
{
	if (index < 1) {
		*address = NULL;
		return 1;
	}
	struct Address *current = *list;
	if (current == NULL) {
		*address = NULL;
		return 2;
	}
	int i = 1;
	while (current != NULL && i != index) {
		current = current->next;
		i++;
	}
	if (i == index && current != NULL) {
		*address = current;
		return 0;
	} else if (i < index && current == NULL) {
		*address = NULL;
		return 2;
	}
        *address = NULL;
        return 3;
}

void add_to_list(struct Address **list, struct Address *address)
{
	struct Address *current = *list;
	if (current == NULL) {
		*list = address;
		return;
	}
	while (current->next != NULL)
		current = current->next;
	current->next = address;
}

void insert_in_list_index(struct Address **list, struct Address *address, int index)
{
	struct Address *current = *list;
	if (current == NULL) {
		*list = address;
		return;
	}
	if (index == 1) {
		address->next = current;
		*list	      = address;
		return;
	}
	int i = 1;
	while (current->next != NULL && i < index - 1) {
		current = current->next;
		i++;
	}
	address->next = current->next;
	current->next = address;
}