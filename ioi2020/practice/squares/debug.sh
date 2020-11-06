#!/bin/bash

problem=squares
grader_name=grader

g++ -std=gnu++17 -O0 -pipe -g -fsanitize=undefined -fsanitize=address -fsanitize=signed-integer-overflow -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
