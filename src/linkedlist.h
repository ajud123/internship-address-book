struct Address {
	char name[30];
	char surname[30];
	char email[30];
	char phone[30];
	struct Address *next;
};

struct Address *create_address_from_line(char *line);
struct Address *create_address(char *name, char *surname, char *email, char *phone);
void add_to_list(struct Address **list, struct Address *address);
void insert_in_list_index(struct Address **list, struct Address *address, int index);