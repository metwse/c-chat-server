#!/bin/bash

tmp_executable=$(mktemp /tmp/c-test.XXXXXX)
app_root=$(dirname $(readlink -fm $0))

gcc -std=gnu18 -g \
    -Wall -Werror \
    $1 $(find $app_root/../src/ $app_root/testutils/ -not -name main.c -name \*.c) \
    -DDEBUG\
    -include $app_root/testutils/tracing.h\
    -o $tmp_executable -lm
if [[ $? -eq 0 ]]; then
    echo "executing: $tmp_executable"
    gdb -q $tmp_executable
fi
