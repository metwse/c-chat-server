#!/bin/bash

tmp_executable=$(mktemp /tmp/c-test.XXXXXX)

gcc -std=c99 -g \
    -Wall -Werror \
    $1 $(find ../src/ ./testutils/ -not -name main.c -name \*.c) \
    -o $tmp_executable -lm
if [[ $? -eq 0 ]]; then
    echo "executing: $tmp_executable"
    gdb -q $tmp_executable
fi
