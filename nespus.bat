@echo off
:eval
nespusgen.exe NMAX 10000 VMAX 1000000000
nespus.exe
nespusbrut.exe
nespuseval.exe
goto eval
