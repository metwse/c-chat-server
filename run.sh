#!/bin/bash

gcc -std=c99 -Wall -Werror $(find ./src -name *.c) -o /tmp/chat
/tmp/chat
