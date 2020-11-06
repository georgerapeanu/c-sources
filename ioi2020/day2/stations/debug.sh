#!/bin/bash

problem=stations
grader_name=stub

g++ -std=gnu++17 -O0 -Wall -pipe -g -fsanitize=address -fsanitize=undefined -fsanitize=signed-integer-overflow -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
