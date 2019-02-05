#!/bin/sh
g++ -Wall -lm -static -DEVAL -o icc.exe -O2 icc.cpp grader.cpp -std=c++11
