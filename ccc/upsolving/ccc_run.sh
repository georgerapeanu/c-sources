#!/bin/bash

for x in *.in;do
    ./_$1 $2 < $x > my_${x%%.*}.out
    echo "done $x"
done
