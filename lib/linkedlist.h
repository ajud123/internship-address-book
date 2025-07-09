#ifndef LINKEDLIST
#define LINKEDLIST

#include "constants.h"

struct Address {
	char name[NAME_LEN];
	char surname[SURNAME_LEN];
	char email[EMAIL_LEN];
	char phone[PHONE_LEN];
	struct Address *next;
};

enum SearchField { NAME = 1, SURNAME, EMAIL, PHONENUMBER };

struct Address *create_address_from_line(char *line);
struct Address *create_address(char *name, char *surname, char *email, char *phone);
int get_address_at_index(struct Address **list, struct Address **address, int index);
struct Address *get_addresses_by_value(struct Address **list, enum SearchField field, char *value);
void add_to_list(struct Address **list, struct Address *address);
void insert_in_list_index(struct Address **list, struct Address *address, int index);
int remove_at_list_index(struct Address **list, int index);
void delete_list(struct Address **list);

#endif