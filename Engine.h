#pragma once 
#include "Theater.h"
#include "CommandLine.h"


// "nlohmann/json" library 

class  Engine {
private:
    static const size_t commandsCount = 17;

    string currentFileName;
    
    Theater* theater = Theater::getInstance();
    bool endProgram;  //if the program should end
    bool unsavedChanges; // when closing file

    bool isValid(CommandLine commandLine); //validates a command line

    void exit();  //exits the program
    void close();  //closes the opened file
    void open(string& filePath); //opens a file
    void save();    //saves changes to file
    void saveAs(string& filePath); //saves chanes to file from path
    void help(); //prints help 

    Engine();
    ~Engine();

public:
    //for Singleton design pattern
    Engine(const Engine& other) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine& other) = delete;
    Engine& operator=(Engine&&) = delete;

    static Engine& getInstance(); //returning the instance of Engine

    void execute(CommandLine commandLine);  //executes given command
    void start(); //the main loop for receiving commands and executing them
};
