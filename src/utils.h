#ifndef UTILS
#define UTILS

struct Address *read_address_book();
void print_address_book(struct Address *book);
void print_single_address(struct Address *address);
int dump_address_book(struct Address *book);
int parse_yes_no(char *input);
void clear_input_buffer();
void read_input(char *msg, char *buf, int size);

#endif