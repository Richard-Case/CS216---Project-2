all: Project2

Project2: main.o Term.o Autocomplete.o SortingList.o
	g++ -o Project2 main.o Term.o Autocomplete.o SortingList.o

main.o: main.cpp
	g++ -c main.cpp

Term.o: Term.cpp Term.h
	g++ -c Term.cpp

Autocomplete.o: Autocomplete.cpp Autocomplete.h
	g++ -c Autocomplete.cpp

SortingList.o: SortingList.cpp SortingList.h Strings.h
	g++ -c SortingList.cpp
