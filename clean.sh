#!/bin/bash

rm ./_*
rm ./*/_*
rm ./*/*/_*
rm ./*/*/*/_*
rm ./*/*/*/*/_*

rm ./*.in
rm ./*/*.in
rm ./*/*/*.in
rm ./*/*/*/*.in
rm ./*/*/*/*/*.in

rm ./*.out
rm ./*/*.out
rm ./*/*/*.out
rm ./*/*/*/*.out
rm ./*/*/*/*/*.out

rm ./*.ok
rm ./*/*.ok
rm ./*/*/*.ok
rm ./*/*/*/*.ok
rm ./*/*/*/*/*.ok

astyle ./*.cpp
astyle ./*/*.cpp
astyle ./*/*/*.cpp
astyle ./*/*/*/*.cpp
astyle ./*/*/*/*/*.cpp

rm ./*.orig
rm ./*/*.orig
rm ./*/*/*.orig
rm ./*/*/*/*.orig
rm ./*/*/*/*/*.orig

ls -lahR
