#pragma once 
#include "Theater.h"
#include "CommandLine.h"
#include "FileReader.h"
#include "FileWriter.h"


class  Engine {
private:
    static const size_t commandsCount = 14;
    const string validCommands[commandsCount] = 
    {"OPEN", "CLOSE", "SAVE", "SAVEAS", "HELP", "EXIT", "ADDEVENT", "FREESEATS", "BOOK", "UNBOOK", "BUY", "BOOKINGS", "CHECK", "REPORT"};

    std::fstream currentFile; //file
    string currFileName;    //file name
    
    Theater* theater;
    static bool endProgram;  //if the program should end
    bool unsavedChanges; // when closing file

    bool isValid(CommandLine cmdl) const; //validates a command line

    void exit();  //exits the program
    void close();  //closes the opened file
    void open(string& filePath); //opens a file
    void save();    //saves changes to file
    void saveAs(string& filePath); //saves chanes to file from path
    void help(); //prints help 
    void execute(CommandLine cmdl);  //executes given command

    int findFileName(const string& filePath) const; //heplper function for finding index of file name
    string checkFileName(const string& filePath) const;  //heplper function for validating file name
    bool openedFile() const; //helper function for checking if file is currently opened

    Engine();
    ~Engine();

public:
    //for Singleton design pattern
    Engine(const Engine& other) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine& operator=(Engine&&) = delete;

    static Engine& getInstance(); //returning the instance of Engine

    void start(); //the main loop for receiving commands and executing them
};
