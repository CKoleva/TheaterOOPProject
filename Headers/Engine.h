/** @file Engine.h
* @brief Contains the declaration of the Engine class which represents the main engine of the program.
* The Engine class is responsible for coordinating the execution of commands, managing the current file and controlling the program flow.
*
* @author Simona Koleva
*/

#pragma once 
#include "Theater.h"
#include "CommandLine.h"
#include "FileReader.h"
#include "FileWriter.h"

/**
 * @class Engine
 * @details Singleton design pattern
 */
class  Engine {
private:
    static const size_t commandsCount = 15;
    const string validCommands[commandsCount] = 
    {"OPEN", "CLOSE", "SAVE", "SAVEAS", "HELP", "EXIT", "ADDEVENT", "FREESEATS", "BOOK", "UNBOOK", "BUY", "BOOKINGS", "CHECK", "REPORT", "MOSTWATCHED"};

    std::fstream currentFile; //!< The currently opened file
    string currFileName;  //!< The name of the currently opened file
    bool fileIsOpen;
    
    static Theater* theater;  //!< Pointer to the Theater instance
    static bool endProgram;  //!< Indicates whether the program should end
    bool unsavedChanges; //!< Indicates unsaved changes when closing the file

    /**
    * @brief Validates a command line.
    * @param cmdl The command line to validate.
    * @return True if the command line is valid, false otherwise.
    */
    bool isValid(CommandLine cmdl) const;

    /**
    * @brief Exits the program.
    */
    void exit(); 

    /**
    * @brief Closes the opened file.
    */
    void close();
    
    /**
    * @brief Opens a file.
    * @param filePath The path of the file to open.
    */
    void open(string& filePath);

    /**
    * @brief Saves changes to the file.
    */
    void save();

    /**
    * @brief Saves changes to a specified file path.
    * @param filePath The path of the file to save to.
    */
    void saveAs(string& filePath);

    /**
    * @brief Prints the help information.
    */
    void help();

    /**
    * @brief Executes a given command.
    * @param cmdl The command line to execute.
    */
    void execute(CommandLine cmdl); 

    /**
    * @brief Helper function to find the index of the file name in a file path.
    * @param filePath The file path to search.
    * @return The index of the file name, or 0 if not found.
    */
    int findFileName(const string& filePath) const;

    /**
    * @brief Helper function to validate the file name in a file path.
    * @param filePath The file path to validate.
    * @return The validated file name.
    */
    string checkFileName(const string& filePath) const;

    /**
    * @brief Helper function to check if a file is currently opened.
    * @return True if a file is currently opened, false otherwise.
    */
    bool openedFile() const; //helper function for checking if file is currently opened

    /**
    * @brief Default constructor for the Engine class.
    */
    Engine();

    /**
    * @brief Destructor.
    */
    ~Engine();

public:
    //for Singleton design pattern
    Engine(const Engine& other) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine& operator=(Engine&&) = delete;

    /**
     * @brief Gets the instance of the Theater (Singleton pattern).
     * @return The instance of the Theater.
     */
    static Engine& getInstance();

    /**
    * @brief Retrieves the theater instance.
    * @return A pointer to the theater instance.
    */
    Theater* getTheater() const;

    /**
    * @brief Starts the main loop for receiving commands and executing them.
    */
    void start();
};
