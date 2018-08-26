@echo off
:eval
designgen.exe NMAX 500 KMAX 6
design.exe
designbrut.exe
designeval.exe
goto eval