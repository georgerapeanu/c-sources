#!/bin/bash

TASK=bubblesort2

g++ -std=c++14 -O2 -pipe -static -s -o ${TASK} grader.cpp ${TASK}.cpp
#g++ -std=c++14 -O0 -g -fsanitize=address -pipe -o ${TASK} grader.cpp ${TASK}.cpp
