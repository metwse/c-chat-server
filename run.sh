#!/bin/bash

. .env
gcc -std=gnu18 -Wall -Werror $(find ./src -name *.c) -o /tmp/chat -lm
/tmp/chat
