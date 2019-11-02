#!/bin/bash

TASK=xylophone

g++ -std=c++14 -O2 -pipe -static -s -o ${TASK} grader.cpp ${TASK}.cpp
