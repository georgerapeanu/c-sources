#!/bin/bash

problem=jelly
grader_name=grader

g++ -std=gnu++17 -O2 -pipe -static -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
