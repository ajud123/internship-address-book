struct Address {
	char name[30];
	char surname[30];
	char email[30];
	char phone[30];
	struct Address *next;
};

enum SearchField { NAME = 1, SURNAME, EMAIL, PHONENUMBER };

struct Address *create_address_from_line(char *line);
struct Address *create_address(char *name, char *surname, char *email, char *phone);
int get_address_at_index(struct Address **list, struct Address **address, int index);
int get_address_by_value(struct Address **list, struct Address **address, enum SearchField field, char *value);
void add_to_list(struct Address **list, struct Address *address);
void insert_in_list_index(struct Address **list, struct Address *address, int index);
int remove_at_list_index(struct Address **list, int index);
void delete_list(struct Address **list);
