CC = g++
CSTD = -std=c++11
OPTFLAGS = -O3 -march=native -flto=auto -funroll-loops

Target := main

all: $(Target).cpp
	$(CC) $(CSTD) $(OPTFLAGS) -o $(Target) $(Target).cpp

clean:
	rm -f *o *.exe $(Target)