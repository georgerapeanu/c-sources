#!/bin/bash

problem=rect

g++ -std=gnu++14 -O0 -Wall -pipe -g -fsanitize=address -o "${problem}" "grader.cpp" "${problem}.cpp"
