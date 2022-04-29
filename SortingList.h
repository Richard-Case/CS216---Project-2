#ifndef SORTINGLIST_H
#define	SORTINGLIST_H

#include <vector>
#include "Strings.h"

template <typename T>
class SortingList
{
   public:
    // Adds the newitem to the end of the current vector.
    void insert(T& newitem);

    // Returns the number of items in the current vector.
    int size() const;

    // Sorts all items in the current vector, in ascending order.
    void sort();

	// Display all the items in the current vector.
	void print() const;

	// Provide the direct access to the vector's items, by index number.
    T& operator[](int& index);


	////**********************************////
	////********SORTING ALGORITHMS********////
	////**********************************////

	// Applies the MERGE SORTING algorithm
    void merge_sort(int (*compare)(T t1, T t2));

    // Applies the SELECTION SORTING algorithm.
    void selection_sort(int (*compare)(T t1, T t2));

    // Applies the BUBBLE SORTING algorithm.
    // pass in function name as the parameter
    // where function defines the comparison between two terms
    void bubbleSort(int (*compare)(T T1, T T2));

    // Applies the SHUFFLE algorithm
    void shuffle();

   private:
    std::vector<T> items;

    // HELPER FUNCTIONS...
    void merge(int& first, int& mid, int& last, int& (*compare)(T t1, T t2)) const;
    void merge_sortHelper(int& min, int& max, int& (*compare)(T t1, T t2));
};


#endif

#include "SortingList.cpp"
