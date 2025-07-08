#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
// #include <unistd.h>
#include "linkedlist.h"
#include "utils.h"
#include "options.h"
#include "constants.h"

static int program_state = 1;
void handle_signal()
{
        //delete_list(&book);
        program_state = 0;
	// exit(0);
}

int main()
{
        struct Address *book;
	book = read_address_book();
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGABRT, handle_signal);
	signal(SIGTERM, handle_signal);
	while (program_state) {
		printf("\033c");
		// printf("Process PID: %i\n", getpid());
		printf("Select the desired action:\n");
		printf("1) Display all records in the address book.\n");
		printf("2) Add a new address to the book (at the end).\n");
		printf("3) Insert a new address to the book at a position.\n");
		printf("4) Delete an address from the book at a position.\n");
		printf("5) Delete the entire address book.\n");
		printf("6) Find address by index.\n");
		printf("7) Find address by name, surname, email or phone number.\n");
		printf("X) Exit.\n");

		char input[OPTIONS_INPUT_LEN];
		// Large buffer used so we don't read 1 char
		// from stdin and then use what's left in the other prompts.
		fgets(input, sizeof(input), stdin);
		if (strlen(input) > 2)
			printf("Unknown command. ");

		int status = parse_input(&book, input);
		if (status == 1) {
			if (book != NULL)
				delete_list(&book);
			return 0;
		}
		printf("Press enter key to continue.");
                // clear_input_buffer();
		if (fgets(input, OPTIONS_INPUT_LEN, stdin) == NULL) {
			if (book != NULL)
				delete_list(&book);
			return 0;
		}
	}
	if (book != NULL)
		delete_list(&book);
	return 0;
}
