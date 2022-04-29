#ifndef AUTOCOMPLETE_H
#define	AUTOCOMPLETE_H

#include <regex>
#include "Term.h"
#include "SortingList.h"

using namespace std;

class Autocomplete
{
    public:
        // Default Constructor...
        Autocomplete();

        // Insert a new term into the current SORTING LIST.
        void insert(Term newterm);

		// Display all the terms in the current SORTING LIST.
        void print();

		// Search for a KEY, between two indecies.
        void search(string key, int& first, int& last);

		// Sort all the terms by query, in lexicographical order.
        void sort();

        // Return the index number of the term whose query prefix-matches the given prefix.
        int binary_search(string prefix);

        // Return all terms that start with the given prefix in descending order, by weight.
        SortingList<Term> Matches(string& prefix, int& maxOutputs);	// Maximum output given by user.
		SortingList<Term> Matches(string& prefix); 					//No maximum output.

    private:
        SortingList<Term> terms;

        int binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index);
};

#endif	/* AUTOCOMPLETE_H */
