#!/bin/bash

gcc -std=c99 -g -Wall -Werror $1.c $(find ../src/ ./testutils/ -not -name main.c -name \*.c) -o /tmp/c-test
if [[ $? -eq 0 ]]; then
    /tmp/c-test
fi
