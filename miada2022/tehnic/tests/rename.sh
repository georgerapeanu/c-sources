#!/bin/bash

if !( [ -d ./infoarena_tests ] ); then
  mkdir ./infoarena_tests
fi

for i in $(ls *.a); do 
  file=${i%.*};
  no_leading_0_file=$(echo $file | sed -E 's/^0*([^0]*.*)$/\1/g');
  cp $file ./infoarena_tests/grader_test$no_leading_0_file.in
  cp $file.a ./infoarena_tests/grader_test$no_leading_0_file.ok
done
