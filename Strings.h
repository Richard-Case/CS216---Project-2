#ifndef STRINGS_H
#define STRINGS_H

#include <string>

// ALERTS
const std::string alertError = "ERROR: ";
const std::string alertInvalidFile = " is not a valid filename. Would you like to try again? (Y/N)\n";
const std::string alertInvalidInput = "INVALID INPUT \nPlease Try Again...\n";
const std::string alertLessThan1 = "Cannot generate less than 1 output.\n";
const std::string alertNegativeInput = "The length of the user's input cannot be negative!\n";
const std::string alertNoFileName = "Please provide the name of a file for processing.\n";
const std::string alertNoQuery = "No matched query!\n";
const std::string alertWarning = "WARNING: ";

// PROMPTS...
const std::string promptContinue = "\nPress ENTER to continue...";
const std::string promptExit = "Exiting program.\n";
const std::string promptExtensionReminder = "Remember to include the filetype extension!\n";
const std::string promptFileName = "Please enter the name of the file you wish to access.\n";
const std::string promptInput = "INPUT: ";
const std::string promptMaxOutputs = "Please enter the maximum number of lines you would like the program to display. (0-9)\n";
const std::string promptResults = "YOUR SEARCH RESULTS: ";
const std::string promptRestart = "Would you like to restart the program?\n";
const std::string promptSearch = "Please enter your search query, or enter \"exit\" to quit the program.\n";
const std::string promptSetMaxOutputs = "Would you like to set a maximum number of outputs to display? (Y/N)\n";

// IOStream Utilities...
const std::string clearTerminal = "\033[2J\033[1;1H";	// Clears the LINUX terminal.

#endif
