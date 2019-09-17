#!/bin/bash
time g++ -Wall -lm -static -DEVAL -o _secret -O2 grader.cpp secret.cpp -std=c++11 && time ./_secret<sample-in-01.txt && cat sample-out-01.txt
