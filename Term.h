#ifndef TERM_H
#define	TERM_H

#include <iostream>
#include <tuple>
#include "Strings.h"

class Term
{
    public:
        // Default constructor...
        Term();

        // Initialize a Term class with a given value for string and weight.
        Term(std::string, long);

		// Compare term1 and term2 in lexicographic order, from index 0 to numOfChars.
        static int compareByPrefix(Term&, Term&, int&);

        // Test to make sure that term1's numerical value is greater than term2's.
        static int compareByWeight(Term&, Term&);

        // Overload the "<" operator, such that it compares the query variable of two term classes.
        friend bool operator<(Term&, Term&);

        // Overload the "<<" operator, such that it outputs the query and weight variables of the term class.
        friend std::ostream& operator<<(std::ostream&, const Term&);

        // Declare the Autocomplete class "friend", so that it can directly access the private date members of Term.
        friend class Autocomplete;

    private:
        std::string query;
        long weight;
};

#endif
