#include "Term.h"

// Default constructor...
Term::Term() {}

// Initialize a Term class with a given value for string and weight.
Term::Term(std::string newQuery, long newWeight)
{
	query = newQuery;
	weight = newWeight;
}

// Compare term1 and term2 in lexicographic order, from index 0 to numOfChars.
int Term::compareByPrefix(Term& term1, Term& term2, int& numOfChars)
{
    if (numOfChars <= 0)
    {
        std::cout << clearTerminal
			<< alertError << alertNegativeInput;

        return 2;
    }

    std::string term1Prefix = (term1.query).substr(0,numOfChars);
    std::string term2Prefix = (term2.query).substr(0,numOfChars);

    if (term1Prefix > term2Prefix) { return 1; }
    if (term1Prefix == term2Prefix) { return 0; }
    else { return -1; }
}

// Test to make sure that term1's numerical value is greater than term2's.
int Term::compareByWeight(Term& term1, Term& term2)
{
	if (term1.weight > term2.weight) { return 1; }
	else if (term1.weight == term2.weight) { return 0; }
	else { return -1; }
}

// Overload the "<" operator, such that it compares the query variable of two term classes.
bool operator<(Term& term1, Term& term2) { return term1.query.compare(term2.query) < 0; }

// Overload the "<<" operator, such that it outputs the query and weight variables of the term class.
std::ostream& operator<<(std::ostream& out, const Term& term1)
{
	out << term1.weight << "	" << term1.query; // The character in the quatations is a tab.
	return out;
}
