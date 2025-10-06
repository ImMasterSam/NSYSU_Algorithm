@echo off

if not exist "main.exe" (
    echo No main.exe found. Compiling...
    mingw32-make.exe
)

if exist "main.exe" (
    main.exe -i data/dt1/point.txt -o ans/ans_dt1.txt -a data/dt1/ans.txt -n "Test 1"
    main.exe -i data/dt2/point.txt -o ans/ans_dt2.txt -a data/dt2/ans.txt -n "Test 2"
    main.exe -i data/dt3/point.txt -o ans/ans_dt3.txt -n "Test 3"
)

