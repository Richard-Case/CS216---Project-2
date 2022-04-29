#ifndef SORTINGLIST_CPP
#define SORTINGLIST_CPP

#include <iostream>
#include <utility>
#include <algorithm>
#include <cassert>
#include "SortingList.h"

// Adds the newitem to the end of the current vector.
template <typename T>
void SortingList<T>::insert(T& newitem) { items.push_back(newitem); }

// Returns the number of items in the current vector.
template <typename T>
int SortingList<T>::size() const { return items.size(); }

// Sorts all items in the current vector, in ascending order.
template <typename T>
void SortingList<T>::sort() { std::sort(items.begin(), items.end()); }

// Display all the items in the current vector.
template <typename T>
void SortingList<T>::print() const
{
    std::cout << clearTerminal
		<< promptResults << std::endl;

    for(size_t i = 0; i < items.size(); i++) { std::cout << items[i] << std::endl; }

    std::cout << std::endl;
}

// Provide the direct access to the vector's items, by index number.
template <typename T>
T& SortingList<T>::operator[](int& index)
{
    assert(index >= 0 && index < size());
    return items[index];
}


////**********************************////
////********SORTING ALGORITHMS********////
////**********************************////


// Applies the MERGE SORTING algorithm
template <typename T>
void SortingList<T>::merge_sort(int (*compare)(T T1, T T2)) { merge_sortHelper(0, items.size() - 1, (*compare)); }

// Applies the SELECTION SORTING algorithm.
template <typename T>
void SortingList<T>::selection_sort(int (*compare)(T T1, T T2))
{
    int min_index = 0;

    for(size_t outerIndex = 0; outerIndex < items.size()-1 ; outerIndex++)
    {
        min_index = outerIndex;

        for(size_t innerIndex = outerIndex+1; innerIndex < items.size(); innerIndex++)
        {
            // Find the index of the minimum value, from the current sequence
            if((*compare)(items[min_index],items[innerIndex]) < 0) { min_index = innerIndex; }
        }

        if (min_index != outerIndex) { swap(items[outerIndex], items[min_index]); }
    }
}

// Applies the BUBBLE SORTING algorithm.
// pass in function name as the parameter
// where function defines the comparison between two terms
template <typename T>
void SortingList<T>::bubbleSort(int (*compare)(T T1, T T2))
{
    for(size_t outerIndex = 1; outerIndex < items.size(); outerIndex++)
    {
        for(size_t innerIndex = 0; innerIndex < items.size() - 1; innerIndex++)
        {
            if((*compare)(items[innerIndex],items[innerIndex+1]) < 0) { swap(items[innerIndex], items[innerIndex+1]); }
        }
    }
}

// Applies the SHUFFLE algorithm
template <typename T>
void SortingList<T>::shuffle()
{
    for(size_t index = items.size()-1; index > 1; index--)
    {
        size_t randomIndex = rand() % (index+1);
        swap(items[index], items[randomIndex]);
    }
}

// HELPER FUNCTIONS...
template <typename T>
void SortingList<T>::merge(int& first, int& mid, int& last, int& (*compare)(T T1, T T2)) const
{
    std::vector<T> temp(items.size());

    int first1 = first;		// Left-most endpoint of first sub-vector.
    int last1 = mid;		// Right-most endpoint of first sub-vector
    int first2 = mid + 1;	// Left-most endpoint of second sub-vector.
    int last2 = last;		// Right-most endpoint of second sub-vector.
    int index = first1;		// Next index open in temp

	// Iterate through both sub-vectors at once, copying the smaller terms in each comparison into the temporary vector.
	// Stop once the end of one sub-vector has been reached.
    while (first1 <= last1 && first2 <= last2)
    {
        if ((*compare)(items[first1],items[first2]) > 0)
        {
            temp[index] = items[first1];
            first1++;
        }
        else
        {
            temp[index] = items[first2];
            first2++;
        }
        index++;
    }

    // Copy the remaining items from the first sub-vector into the temporary vector, if any exist.
    while (first1 <= last1)
    {
        temp[index] = items[first1];
        first1++;
        index++;
    }

    // Copy the remaining items from the second sub-vector into the temporary vector, if any exist.
    while (first2 <= last2)
    {
        temp[index] = items[first2];
        first2++;
        index++;
    }

    // Copy the merged data in the temporary vector into the original vector, overwriting what is currently there.
    for (int i = first; i <= last; i++)
        items[i] = temp[i];
}

template <typename T>
void SortingList<T>::merge_sortHelper(int& min, int& max, int& (*compare)(T T1, T T2))
{
    if (min < max)
    {
        int mid = (min + max) / 2;
        merge_sortHelper(min, mid, (*compare));
        merge_sortHelper(mid + 1, max, (*compare));
        merge(min, mid, max, (*compare));
    }
}

#endif
