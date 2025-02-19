#!/bin/bash

gcc -std=c99 -Wall -Werror $1.c $(find ../src/ -not -name main.c -name \*.c) -o /tmp/c-test
if [[ $? -eq 0 ]]; then
    /tmp/c-test
fi
