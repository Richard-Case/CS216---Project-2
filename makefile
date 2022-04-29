all: Project2

Project2: Project2.o Term.o Autocomplete.o SortingList.o
	g++ -o Project2 Project2.o Term.o Autocomplete.o SortingList.o

Project2.o: Project2.cpp
	g++ -c Project2.cpp

Term.o: Term.cpp Term.h
	g++ -c Term.cpp

Autocomplete.o: Autocomplete.cpp Autocomplete.h
	g++ -c Autocomplete.cpp

SortingList.o: SortingList.cpp SortingList.h
	g++ -c SortingList.cpp
