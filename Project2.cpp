/*
	Course: CS216-002
	Project: 2 - Autocomplete Project

	CHANGELOG:
		20220403
	 		- Copied Lab9 files into Prject 2.
			- Refactored files, renaming things for preference, and removing STANDARD LIBRARY using commands and redundant include statements.
			- Edited main CPP function to search for 3 arguments from the user.
			- Completed userInput conversion, removing excess whitespace.
			- Re-worked the Autocomplete function "Matches" to not account for letter case in its search.
				- Bonus work completed.
		20220404
			- Re-worked program to account for incorrect input from the user at every step.
			- Re-worked program to allow the user to restart if they want.
			- Migrated all strings to an external file: Strings.h
 */

#include <fstream>
#include <sstream>
#include <ctime>
#include "Autocomplete.h"

void ConstructDatabase(Autocomplete&, std::ifstream&);
void GetFileName(bool&, std::string&);
void WaitForUser();

int main(int argc, char** argv)
{
	bool continueRunning = true;

	do
	{
		const int ARGUMENTS = 3;
		int arguments = argc;
		int maxOutputs = 0;
		std::string userInput;
		std::string fileName;
		bool validInput = false;
		bool fileNameSet = false;
		std::ifstream inputFile;

	    // Check to make sure the correct number of arguments were given, and get them from the user if not.
		do
		{
			switch (arguments)
			{
			// If the user has not provided a first argument.
			case 1:
				std::cout << clearTerminal
					<< alertError << alertNoFileName
					<< promptInput;
				GetFileName(fileNameSet, fileName);

				arguments++;
				break;

			// If the user has not provided a second argument.
			case 2:
				std::cout << clearTerminal
					<< promptSetMaxOutputs
					<< promptInput;
		        std::getline(std::cin, userInput);

				if (std::toupper(userInput[0]) == 'Y')
				{
					std::cout << clearTerminal;

					do
					{
						std::cout << promptMaxOutputs
							<< promptInput;

						// Get the maximum number of outputs from the user, then clear the excess whitespace from the input stream.
						std::cin >> maxOutputs;
						std::cin.ignore(numeric_limits<streamsize>::max(), '\n');

						// Ensure that maxOutputs is positive.
						if (maxOutputs <= 0)
						{
							std::cout << clearTerminal
								<< alertError << alertLessThan1;
							validInput = false;
						}
						else
						{
							validInput = true;
						}
					} while (!validInput);
				}

				arguments++;
				break;

			// The default case should never be accessed.
			default:
				break;
			}

		} while (arguments < ARGUMENTS);

	    // Ensure that the user's file can be openned correctly.
		if (!fileNameSet)
		{
			fileName = argv[1];

			// Ensure that the file name provided includes the ".txt" extension.
			if (fileName.substr(fileName.length()-4, 4) != ".txt")
			{
				fileName += ".txt";
			}
		}

		inputFile.open(fileName);	// Open the file, using the file name provided by the user.

		// If the user has provided an invalid file name...
		while(!inputFile.good())
		{
			// Ask the user if they would like to try again.
			std::cout << clearTerminal << fileName << alertInvalidFile
				<< promptInput;
			std::getline(std::cin, userInput);

			if (std::toupper(userInput[0]) == 'Y') // If yes...
			{
				if (fileName.substr(fileName.length()-4, 4) != ".txt")
				{
					std::cout << promptExtensionReminder;
				}

				std::cout << clearTerminal
					<< promptFileName
					<< promptInput;
				GetFileName(fileNameSet, fileName);

				inputFile.open(fileName);
			}
			else // If no...
			{
				std::cout << clearTerminal
					<< promptExit;
				WaitForUser();
				return 0;
			}
		}

	    // Construct the Autocomplete object by reading in the terms from the userInput file, one line at a time.
	    Autocomplete autocomplete;
	    ConstructDatabase(autocomplete, inputFile);

		// If three arguments were original provided, convert argument at INDEX 2 from CHAR to INT in order to assign it to maxOutputs.
		if (argc == 3)
		{
			std::istringstream iss(argv[2]);
			iss >> maxOutputs;

			// Ensure that maxOutputs is positive.
			do
			{
				if (maxOutputs <= 0)
				{
					std::cout << clearTerminal
						<< alertError << alertLessThan1;
					validInput = false;

					std::cout << promptMaxOutputs;
					std::cin >> maxOutputs;
					std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
				}
				else
				{
					validInput = true;
				}
			} while (!validInput);
		}

	    do
	    {
		    std::cout << clearTerminal << promptSearch
				<< promptInput;
		    std::getline(std::cin, userInput);

			// Remove excess whitespace from the user's input.
			std::string correctedInput = "";
			bool firstCharEncountered = false;
			bool firstWordEncountered = false;

			for (int index = 0; index < userInput.length(); index++)
			{
				if (((userInput[index] != ' ') && (userInput[index] != '	')) && !firstWordEncountered)
				{
					correctedInput += std::tolower(userInput[index]);
					firstWordEncountered = true;
					firstCharEncountered = true;
				}
				else if (((userInput[index] != ' ') && (userInput[index] != '	')) && !firstCharEncountered)
				{
					correctedInput += " ";
					correctedInput += std::tolower(userInput[index]);
					firstCharEncountered = true;
				}
				else if ((userInput[index] != ' ') && (userInput[index] != '	'))
				{
					correctedInput += std::tolower(userInput[index]);
				}
				else
				{
					firstCharEncountered = false;
				}
			}

			if (correctedInput != "exit")
			{
				SortingList<Term> matchedTerms;

				// Determine which Matches overload to use, based on the maximum number of outputs provided by the user.
				if (maxOutputs == 0) { matchedTerms = autocomplete.Matches(correctedInput); }
				else { matchedTerms = autocomplete.Matches(correctedInput, maxOutputs); }

		        if (matchedTerms.size() == 0)
		        {
		            std::cout << clearTerminal
						<< alertWarning << alertNoQuery;
					WaitForUser();
		        }
		        else
		        {
		            matchedTerms.print();
					WaitForUser();
		        }
			}
			else { continueRunning = false; }

	    } while (continueRunning);

		std::cout << clearTerminal
			<< promptRestart
			<< promptInput;
		std::getline(std::cin, userInput);

		if (std::toupper(userInput[0]) == 'Y') { continueRunning = true; }

	} while (continueRunning);

	std::cout << clearTerminal
		<< promptExit;
	WaitForUser();

	std::cout << clearTerminal;
    return 0;
}

void ConstructDatabase(Autocomplete& autocomplete, std::ifstream& inputFile)
{
	long weight;
    std::string query;

	while (!inputFile.eof())
    {
        inputFile >> weight >> std::ws;
        std::getline(inputFile, query);
        if (query != "")
        {
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }
    }
}

void GetFileName(bool& fileNameSet, std::string& fileName)
{
	std::getline(std::cin, fileName);

	// Ensure that the ".txt" is included.
	if(fileName.substr(fileName.length()-4, 4) != ".txt")
	{
		fileName += ".txt";
	}

	fileNameSet = true;
}

void WaitForUser()
{
	std::string pauseInput = "";
	std::cout << promptContinue;
	getline(std::cin, pauseInput);
}
