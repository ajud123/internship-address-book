#include "linkedlist.h"
#include "options.h"
#include <string.h>
#include <stdlib.h>

#define DELIMITER ","

/*
 * Creates and returns an address struct from a provided CSV line string.
 * The CSV format is as follows:
 * `name,surname,email,phone`
 * If any of the inputs exceed allowed field length, returns NULL.
 */
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

	if (name == NULL)
		return NULL;
	if (surname == NULL)
		return NULL;
	if (email == NULL)
		return NULL;
	if (phone == NULL)
		return NULL;
	if (strlen(name) > NAME_LEN - 1)
		return NULL;
	if (strlen(surname) > SURNAME_LEN - 1)
		return NULL;
	if (strlen(email) > EMAIL_LEN - 1)
		return NULL;
	if (strlen(phone) > PHONE_LEN - 1)
		return NULL;
	// Ensure we're not leaving trailing whitespace in the phone number
	int phonelen = strlen(phone);
	if (phone[phonelen - 1] == '\n')
		phone[phonelen - 1] = '\0';

	struct Address *addr = create_address(name, surname, email, phone);
	return addr;
}

/*
 * Either returns the pointer to the newly created address or segfaults.
 */
struct Address *create_address(char *name, char *surname, char *email, char *phone)
{
	struct Address *addr = malloc(sizeof(struct Address));
	addr->next	     = NULL;
	strncpy(addr->name, name, NAME_LEN);
	strncpy(addr->surname, surname, SURNAME_LEN);
	strncpy(addr->email, email, EMAIL_LEN);
	strncpy(addr->phone, phone, PHONE_LEN);
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
		return 3;
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

struct Address *get_addresses_by_value(struct Address **list, enum SearchField field, char *value)
{
	struct Address *current = *list;
	char *location;
	if (current == NULL) {
		return NULL;
	}
	switch (field) {
	case NAME:
		location = current->name;
		break;
	case SURNAME:
		location = current->surname;
		break;
	case EMAIL:
		location = current->email;
		break;
	case PHONENUMBER:
		location = current->phone;
		break;
	}
	// Pointer arithmetics
	int offset		      = (void *)location - (void *)current;
	int i			      = 1;
	struct Address *foundElements = NULL;
	while (current != NULL) {
		// Cast to void* otherwise the arithmetics fail
		if (strcmp((char *)((void *)current + offset), value) == 0) {
			struct Address *copy = create_address(current->name, current->surname, current->email,
							      current->phone);
			add_to_list(&foundElements,copy);
		}
		current = current->next;
		i++;
	}
	return foundElements;
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
	if (index < 1)
		index = 1;
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

/*
 * Removes an element at a given list index.
 * Returns 0 if the element was found and removed.
 * Returns 1 if the element was not found.
 */
int remove_at_list_index(struct Address **list, int index)
{
	struct Address *current = *list;
	if (current == NULL) {
		return 1;
	}
	if (index == 1) {
		struct Address *next = current->next;
		free(*list);
		*list = next;
		return 0;
	}
	int i = 1;
	while (current->next != NULL && i < index - 1) {
		current = current->next;
		i++;
	}
	if (current->next != NULL && i == index - 1) {
		struct Address *removed = current->next;
		current->next		= removed->next;
		free(removed);
		return 0;
	}
	return 1;
}

void delete_list(struct Address **list)
{
	struct Address *next;
	while (*list != NULL) {
		next = (*list)->next;
		free(*list);
		*list = next;
	}
}
