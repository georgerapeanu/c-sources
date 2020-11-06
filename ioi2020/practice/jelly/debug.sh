#!/bin/bash

problem=jelly
grader_name=grader

g++ -std=gnu++17 -O0 -pipe -g -fsanitize=address -fsanitize=undefined -fsanitize=signed-integer-overflow -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
