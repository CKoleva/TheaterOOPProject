/** @file CommandLine.h
 *  @brief A class that represents a command line with arguments.
 *  
 *  @author Simona Koleva
 */

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
    vector<string> argv; //!< Contains the command and arguments.

    /**
     * @brief Gets the count of quotes in a string.
     * @param str The string to count the quotes in.
     * @return The count of quotes in the string.
     */
    size_t getQuotesCount(const string& str);


    /**
     * @brief Converts a string to uppercase.
     * @param str The string to convert.
     * @return The uppercase version of the string.
     */
    string toUpper(string str);

    /**
     * @brief Removes extra empty spaces from a string.
     * @param line The string to remove the extra empty spaces from.
     */
    void removeExtraEmptySpaces(string& line);

    /**
     * @brief Parses the command line string into individual arguments.
     * @param commandLine The command line string to parse.
     */
    void parseCommandLine(string commandLine);
    
public:
    /**
     * @brief Parametric constructor for the CommandLine class.
     * @param commandLine The command line string.
     */
    CommandLine(string commandLine);

    /**
     * @brief Gets the number of arguments in the command line.
     * @return The number of arguments.
     */
    size_t getSize() const;

    /**
     * @brief Gets the vector of arguments.
     * @return The vector of arguments.
     */
    vector<string> getArgv();
};