EXE:=exe
$(EXE) : main.cpp list.cpp
	g++ -std=c++11 -g -ggdb $^  -Wall -pedantic -o $@

list.cpp : list.hpp

clean:
	rm $(EXE)

