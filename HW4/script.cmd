@echo off

if exist "Makefile" (
    echo Compiling main.cpp ...
    mingw32-make.exe
)

if exist "main.exe" (
    main.exe -i data/dt1/point.txt -o ans_dt1 -a data/dt1/ans.txt -n "Test Case 1" -p
    main.exe -i data/dt2/point.txt -o ans_dt2 -a data/dt2/ans.txt -n "Test Case 2" -p
    main.exe -i data/dt3/point.txt -o ans_dt3 -n "Test Case 3" -p
    main.exe -i data/dt4/point.txt -o ans_dt4 -n "Test Case 4" -p
)

