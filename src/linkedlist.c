#include "linkedlist.h"
#include <string.h>
#include <stdlib.h>

struct Address *create_address_from_line(char *line)
{
	char *name;
	char *surname;
	char *email;
	char *phone;

	name	= strtok(line, delimiter);
	surname = strtok(NULL, delimiter);
	email	= strtok(NULL, delimiter);
	phone	= strtok(NULL, delimiter);

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
        if(index == 1) {
                address->next = current;
		*list = address;
                return;
        }
        int i = 1;
	while (current->next != NULL && i < index-1){
		current = current->next;
                i++;
        }
        address->next = current->next;
	current->next = address;
}