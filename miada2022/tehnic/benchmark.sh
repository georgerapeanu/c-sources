#!/bin/bash

if !( [ -d ./infoarena_tests ] ); then
  mkdir ./infoarena_tests
fi

for i in $(ls ./tests/*.a); do 
  file=${i%.*};
  ./_statistcs < $file > /dev/null;
done
