#!/bin/env bash
rm address_book
gcc -Wall -Wextra -g -o address_book ./src/main.c ./src/utils.c ./src/linkedlist.c -I/home/studentas/part-2-address-book/src -L/home/studentas/part-2-address-book/src