#!/bin/bash

for x in *.in; do
    ./$1 < $x > my_${x%%.*}.out 2> /dev/null
    if [ -f ${x%%.*}.out ]; then
      diff -w my_${x%%.*}.out ${x%%.*}.out;
    fi
    echo "done $x"
done
