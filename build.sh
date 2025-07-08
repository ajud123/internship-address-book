#!/bin/env bash
rm ./bin/address_book
if [ ! -d "./bin" ]; then
        mkdir ./bin;
fi
gcc -Wall -Wextra -g -o ./bin/address_book ./src/main.c ./src/utils.c ./src/linkedlist.c -I/home/studentas/part-2-address-book/src -L/home/studentas/part-2-address-book/src