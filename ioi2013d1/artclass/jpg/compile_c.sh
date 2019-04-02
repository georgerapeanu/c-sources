#!/bin/bash

NAME=artclass

/usr/bin/gcc -std=gnu99 -DEVAL -static -O2 -o $NAME grader.c graderlib.c $NAME.c -lm -ljpeg
