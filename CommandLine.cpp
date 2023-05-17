#include "CommandLine.h"
#include <stdexcept>
#include <iostream>

CommandLine::CommandLine(string commandLine) {
    if (commandLine.size() == 0) {
        throw std::invalid_argument("No command entered.");
    } 
    else if(getQuotesCount(commandLine) % 2 == 1) {
        throw std::invalid_argument("Count of quotes is invalid.");
    } else {
        parseCommandLine(commandLine);
    }
}

size_t CommandLine::getQuotesCount(const string& str) {
    size_t count = 0;
    const size_t size = str.size();

    for (size_t i = 0; i < size; i++)
    {
        if (str[i] == '\"')
        {
            ++count;
        }
    }
    
    return count;
}

string CommandLine::toUpper(string str) {
    string result = "";
    const size_t size = str.size();

    for (size_t i = 0; i < size; i++)
    {
        result.push_back(toupper(str[i]));
    }

    return result;
}

void CommandLine::removeExtraEmptySpaces(string& line) {
    size_t size = line.size(); 

    size_t currIdx = 0;
    while (line[currIdx] == ' ')  // Finds the first char which is not ' '
    {
        ++currIdx;
    }
    
    line.erase(line.begin(), line.begin()+currIdx-1);
    while (line[line.size() - 1] == ' ')   // Removes the extra empty spaces in the end
    {
        line.pop_back();
    }
    

    size = line.size();
    for (size_t i = 1; i < size; i++)    // Removes the extrea white spaces in between
    {
        if (line[i] == ' ' && line[i-1] == ' ')
        {
            line.erase(line.begin()+i);
            --size;
        }        
    }
}

void CommandLine::parseCommandLine(string commandLine) {
    removeExtraEmptySpaces(commandLine);

    size_t size = commandLine.size();
    string word = "";
    for (size_t i = 1; i < size; i++)
    {
        if (commandLine[i] == '\"')
        {
            
            ++i;
            while (commandLine[i] != '\"')
            {
                word.push_back(commandLine[i]);
                ++i;
            }

            if (word != "")
            {
                this->argv.push_back(word);
                word = "";
            }               
        }
        else if (commandLine[i] == ' ')
        {
            if(word != "") {
                this->argv.push_back(word);
                word = "";
            }            
        }
        else {
            word.push_back(commandLine[i]);    

            if (i == size - 1)
            {
                argv.push_back(word);
            }
        }   
    }
    
    this->argv[0] = toUpper(this->argv[0]);
}


vector<string> CommandLine::getArgv() {
    return this->argv;
}