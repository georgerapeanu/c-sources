#!/bin/bash

problem=routers
grader_name=grader

g++ -std=gnu++14 -O2 -pipe -static -o "${problem}" "${grader_name}.cpp" "${problem}.cpp"
