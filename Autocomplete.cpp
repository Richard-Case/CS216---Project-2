#include "Autocomplete.h"

// Default Constructor...
Autocomplete::Autocomplete() {}

// Insert a new term into the current SORTING LIST.
void Autocomplete::insert(Term newterm) { terms.insert(newterm); }

// Display all the terms in the current SORTING LIST.
void Autocomplete::print() {}

// Search for a KEY, between two indecies.
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
	int initial = binary_search(key);
	std::cout << "Initial Key: " << initial << std::endl << std::endl;

	for (int index = initial; index > 0; index--)
	{
		if (terms[index].query.substr(0,key.length()) == key)
		{
			firstIndex = index;
		}
	}

	for (int index = initial; index < terms.size(); index++)
	{
		if (terms[initial].query.substr(0,key.length()) == key)
		{
			lastIndex = index;
		}
	}
}

// Sort all the terms by query, in lexicographical order.
void Autocomplete::sort() { terms.sort(); }

// Return the index number of the term whose query prefix-matches the given prefix.
int Autocomplete::binary_search(string prefix) { return binary_searchHelper(terms, prefix, 0, terms.size()); }

// Return all terms that start with the given prefix in descending order, by weight.
SortingList<Term> Autocomplete::Matches(string& prefix, int& maxOutputs) // Maximum output given by user.
{
	SortingList<Term> matches;

	for (int index = 0; index < terms.size(); index++)
	{
		std::string newSubstring = "";

		for (int stringIndex = 0; stringIndex < prefix.length(); stringIndex++)
		{
			newSubstring += tolower(terms[index].query[stringIndex]);
		}

		if (newSubstring == prefix)
		{
			matches.insert(terms[index]);
		}
	}

	// BUBBLE SORT algorithm.
	for (int index = 0; index < matches.size(); index++)
	{
		for (int testIndex = index; testIndex < matches.size(); testIndex++)
		{
			if (matches[index].weight < matches[testIndex].weight)
			{
				std::swap(matches[index],matches[testIndex]);
			}
		}
	}

	if (maxOutputs > matches.size())
	{
		return matches;
	}
	else
	{
		SortingList<Term> shortenedMatches;

		for (int index = 0; index < maxOutputs; index++) { shortenedMatches.insert(matches[index]); }

		return shortenedMatches;
	}
}

// Return all terms that start with the given prefix in descending order, by weight.
SortingList<Term> Autocomplete::Matches(string& prefix) // No maximum output.
{
	SortingList<Term> matches;

	for (int index = 0; index < terms.size(); index++)
	{
		std::string newSubstring = "";

		for (int stringIndex = 0; stringIndex < prefix.length(); stringIndex++)
		{
			newSubstring += tolower(terms[index].query[stringIndex]);
		}

		if (newSubstring == prefix)
		{
			matches.insert(terms[index]);
		}
	}

	// BUBBLE SORT algorithm.
	for (int index = 0; index < matches.size(); index++)
	{
		for (int testIndex = index; testIndex < matches.size(); testIndex++)
		{
			if (matches[index].weight < matches[testIndex].weight)
			{
				std::swap(matches[index],matches[testIndex]);
			}
		}
	}

	return matches;
}


////**********************************////
////*********PRIVATE**METHODS*********////
////**********************************////

int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if(right_index < left_index)
    {
        int KEY_NOT_FOUND = -1;
        return KEY_NOT_FOUND;
    }
    else
    {
        Term keyterm(key, 0);
        int r = key.length();
        int middle = (left_index + right_index) / 2;

        if(Term::compareByPrefix(keyterm,terms[middle],r) > 0)
        {
            return binary_searchHelper(terms, key, left_index, middle - 1);

        }
        else if(Term::compareByPrefix(keyterm,terms[middle],r)  < 0)
        {
            return binary_searchHelper(terms, key, middle + 1, right_index);
        }
        else
        {
            return middle;
        }
    }
}
