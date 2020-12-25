#!/usr/bin/env bash

g++ -DEVAL -O0 -fsanitize=address,undefined,signed-integer-overflow -g -std=c++11 grader.cpp floppy.cpp -o floppy
