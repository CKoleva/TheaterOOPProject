#pragma once

#include <vector>
#include <string>
#include <cstddef>

using std::size_t;
using std::string;
using std::vector;

class CommandLine
{
private:
    vector<string> argv; //contains command and arguments

    size_t getQuotesCount(const string& str); //get the count of quotes in a string

    string toUpper(string str); //helps create case-insensitive command input

    void removeExtraEmptySpaces(string& line); //removes unnessesary empty spaces

    void parseCommandLine(string commandLine); //parses the command line to arguments in argv
    
public:
    CommandLine(string commandLine); //parametric constructor

    size_t getSize() const; //returns number of arguments  ???? is it useless

    vector<string> getArgv();
};