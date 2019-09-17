#!/bin/bash
#time g++ -Wall -lm -static -DEVAL -o _factories -O2 grader.cpp factories.cpp -std=c++11 && time ./_factories<sample-in-01.txt && cat sample-out-01.txt
time g++ -Wall -lm -g -fsanitize=address -DEVAL -o _factories -O0 grader.cpp factories.cpp -std=c++11 && time ./_factories<sample-in-01.txt && cat sample-out-01.txt
