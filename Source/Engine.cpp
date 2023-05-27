#include "../Headers/Engine.h"

Theater* Engine::getTheater() const {
    return this->theater;
}

bool Engine::endProgram = false;

Engine::~Engine() {         //how is the theater created and where
    theater = nullptr;
    Theater::deleteTheater();
    if (currentFile.is_open())
    {
        currentFile.close();
    }
}

Theater* Engine::theater = Theater::getInstance();

Engine::Engine() {          //default constructor
    fileIsOpen = false;
    unsavedChanges = false;
    currFileName = "";
}

Engine& Engine::getInstance()
{
    static Engine engine;
    return engine;
}

void Engine::start() {
    string commandLine;

    while (endProgram == false)
    {
        std::cout << "> ";
        getline(std::cin, commandLine);
        CommandLine cmdl(commandLine);
        try
        {
            this->execute(cmdl);
        }
        catch(const std::bad_alloc& mmry)
        {
            std::cout << "Memory problem" << std::endl;
        }
        catch(const std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    
}

void Engine::execute(CommandLine cmdl) {
    if (!isValid(cmdl))
    {
        return;
    }

    string command = cmdl.getArgv()[0];
    
    if (command == "OPEN")
    {
        open(cmdl.getArgv()[1]);
    }
    else if (command == "SAVE")
    {
        if (!openedFile())
        {
            return;
        }

        save();
    }
    else if (command == "SAVEAS")
    {
        if (!openedFile())
        {
            return;
        }

        saveAs(cmdl.getArgv()[1]);
    }
    else if (command == "CLOSE")
    {
        if (!openedFile())
        {
            return;
        }

        close();
    }
    else if (command == "HELP")
    {
        help();
    }
    else if (command == "EXIT")
    {
        exit();
    }
    else if (command == "ADDEVENT")
    {
        if (!openedFile())
        {
            return;
        }
        
        Date date(cmdl.getArgv()[1]);
        string hallName = cmdl.getArgv()[2];
        string eventName = cmdl.getArgv()[3];
        theater->addEvent(date, hallName, eventName);
        makeAllTicketsFree(this->theater);
        unsavedChanges = true;

        std::cout << "Event \"" + eventName + "\" has been successfully added.\n";
    }
    else if (command == "FREESEATS")
    {
        if (!openedFile())
        {
            return;
        }

        Date date(cmdl.getArgv()[1]);
        string eventName = cmdl.getArgv()[2];
        theater->displayAvailableSeats(eventName, date);
    }
    else if (command == "BOOK")
    {
        if (!openedFile())
        {
            return;
        }

        size_t row = std::stoi(cmdl.getArgv()[1]);
        size_t seat = std::stoi(cmdl.getArgv()[2]);
        Date date(cmdl.getArgv()[3]);
        string eventName = cmdl.getArgv()[4];
        string note = cmdl.getArgv()[5];
        theater->bookTicket(row, seat, date, eventName, note);
        unsavedChanges = true;
        
        std::cout << "Ticket booked successfully.\n";
    }
    else if (command == "UNBOOK")
    {
        if (!openedFile())
        {
            return;
        }

        size_t row = std::stoi(cmdl.getArgv()[1]);
        size_t seat = std::stoi(cmdl.getArgv()[2]);
        Date date(cmdl.getArgv()[3]);
        string eventName = cmdl.getArgv()[4];
        theater->unbookTicket(row, seat, date, eventName);
        unsavedChanges = true;

        std::cout << "Ticket unbooked successfully.\n";
    }
    else if (command == "BUY")
    {
        if (!openedFile())
        {
            return;
        }

        size_t row = std::stoi(cmdl.getArgv()[1]);
        size_t seat = std::stoi(cmdl.getArgv()[2]);
        Date date(cmdl.getArgv()[3]);
        string eventName = cmdl.getArgv()[4];
        theater->purchaseTicket(row, seat, date, eventName);
        unsavedChanges = true;

        std::cout << "Ticket purchased successfully.\n";
    }
    else if (command == "CHECK")
    {
        if (!openedFile())
        {
            return;
        }

        theater->check(cmdl.getArgv()[1]);
    }
    else if (command == "BOOKINGS" && cmdl.getSize() == 3)
    {
        if (!openedFile())
        {
            return;
        }

        Date date(cmdl.getArgv()[1]);
        string eventName = cmdl.getArgv()[2];
        theater->displayBookings(date, eventName);
    }
    else if (command == "BOOKINGS" && cmdl.getSize() == 2)
    {
        if (!openedFile())
        {
            return;
        }

        try
        {
            Date date(cmdl.getArgv()[1]);
        }
        catch(const std::runtime_error& notADate)
        {
            theater->displayBookings(cmdl.getArgv()[1]);            //is this valid
            return;
        }

        Date date(cmdl.getArgv()[1]);
        theater->displayBookings(date);
        
    }
    else if(command == "REPORT" && cmdl.getSize() == 3)
    {
        if (!openedFile())
        {
            return;
        }

        Date dateFrom(cmdl.getArgv()[1]);
        Date dateTo(cmdl.getArgv()[2]);
        theater->report(dateFrom, dateTo);
    }
    else if (command == "REPORT" && cmdl.getSize() == 4)
    {
        if (!openedFile())
        {
            return;
        }

        Date dateFrom(cmdl.getArgv()[1]);
        Date dateTo(cmdl.getArgv()[2]);
        string hallName = cmdl.getArgv()[3];
        theater->report(dateFrom, dateTo, hallName);
    }
    else if (command == "MOSTWATCHED" && cmdl.getSize() == 1)
    {
        if (!openedFile())
        {
            return;
        }

        theater->mostWatchedEventsStatistic();
    }
}

bool Engine::isValid(CommandLine cmdl) const {
    string command = cmdl.getArgv()[0];
    size_t argc = cmdl.getSize();
    bool found = false;

    for (size_t i = 0; i < commandsCount; i++)
    {
        if(command == validCommands[i])
            found = true;
    }
    
    if (found == false)
    {
        std::cout << "Invald command! Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "HELP" || command == "SAVE" || command == "CLOSE" || command == "EXIT") && argc != 1)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "OPEN" || command == "SAVEAS" || command == "CKECK") && argc != 2)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "FREESEATS") && argc != 3)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

     if (command == "BOOKINGS" && argc != 2 && argc != 3)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }
    
    if (command == "REPORT" && argc != 3 && argc != 4)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "ADDEVENT") && argc != 4)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "BUY" || command == "UNBOOK") && argc != 5)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }
    
    if ((command == "BOOK") && argc != 6)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }

    if ((command == "MOSTWATCHED") && argc != 1)
    {
        std::cout << "Invalid number of arguments!. Type \"help\" to see all supported commands.\n";
        return false;
    }
    
    
    return true;
}

void Engine::exit() {
    endProgram = true;
    if (currentFile.is_open())
    {                               
        currentFile.close();
    }
    std::cout << "Exiting the program..." << std::endl;
}

void Engine::close() {
    if (unsavedChanges)
    {
        std::cout << "There are unsaved changes. Are you sure you want to close the currently opened file?\n" 
        << "Type \'y\' to close or \'n\' to cancel.\n";
    }
    else  {
        fileIsOpen = false;
        theater->free();
        std::cout << "Successfully closed \"" + currFileName + "\".\n";
        return;
    }
    char answer;
    bool validAnswer = false;
    while (!validAnswer)
    {
        std::cout << "> ";
        std::cin >> answer;
        std::cin.ignore();
        if (toupper(answer) == 'Y')
        {
            validAnswer = true;
            unsavedChanges = false;
            fileIsOpen = false;
            theater->free();
            std::cout << "Successfully closed \"" + currFileName + "\".\n";
            //close !! handle memory !! unsavedChanges = false !! validAnswer = true
        }
        else if (toupper(answer) == 'N')
        {
            validAnswer = true;
            std::cout << "Operation canceled.\n";
        }
        else {
            std::cout << "Invalid answer. Type \'y\' to close or \'n\' to cancel.\n";
        }
    }
}

bool Engine::openedFile() const {
    return fileIsOpen;
}

int Engine::findFileName(const string& filePath) const {    
    int idx = filePath.find_last_of('\\');

    if (idx == std::string::npos)
    {
        return 0;
    }

    return idx + 1;
}

string Engine::checkFileName(const string& filePath) const {
    int fileNameIdx = findFileName(filePath);

    string fileName = filePath.substr(fileNameIdx);
    size_t nameSize = fileName.size();
    if (nameSize < 6)
    {
        std::cout << "Invalid file. This program supports XXX.json files where XXX is the name of the file.\n";
        return "";
    }
    
    string extention = fileName.substr(fileName.size() - 5);
    if (extention != ".json")
    {
        std::cout << "Invalid file. This program supports XXX.json files where XXX is the name of the file.\n";
        return "";
    }

    return fileName;
}

void Engine::open(string& filePath) {
    string fileName = checkFileName(filePath);
    if (fileName == "")
    {
        return;
    }
    
    if (openedFile())
    {
        std::cout << "Invalid operation. You need to close the currently opened file first.\n";
        return;
    }

    currFileName = fileName;

    // Check if the file exists
    std::ifstream existingFile(fileName);
    bool fileExists = existingFile.good();
    existingFile.close();

    if (!fileExists) {
        // Create a new empty file
        currentFile.open(fileName, std::ios::out);
        if (!currentFile.is_open()) {
            std::cout << "Failed to create \"" << fileName << "\".\n";
            return;
        }
        std::cout << "Successfully created \"" << currFileName << "\".\n";
        currentFile.close();
    } else {
        // Open the existing file
        currentFile.open(fileName, std::ios::in);
        if (!currentFile.is_open()) {
            std::cout << "Failed to open \"" << fileName << "\".\n";
            return;
        }
        std::cout << "Successfully opened \"" << currFileName << "\".\n";
        FileReader::loadTheaterData(this->theater, currentFile);
        currentFile.close();
    }
    fileIsOpen = true;
}

void Engine::help() {
    std::cout << "The following commands are supported:\n"
    << "open <file>	        opens <file>\n" 
    << "close			closes currently opened file\n" 
    << "save			saves the currently open file\n"
    << "saveas <file>	        saves the currently open file in <file>\n"
    << "help			prints this information\n"
    << "exit			exists the program\n\n"
    << "addEvent <date> <hall> <name>\n"
    << "freeseats <date> <name>\n"
    << "book <row> <seat> <date> <name> <note>\n"
    << "unbook <row> <seat> <date> <name>\n"
    << "buy <row> <seat> <date> <name>\n"
    << "bookings [<date>] [<name>]\n"
    << "check <code>\n"
    << "report <from> <to> [<hall>]\n"
    << "\nNote: Arguments in \'[]\' are optional.\n\n";
}

void Engine::save() {
    fstream inOutMode(currFileName, std::ios::out);
    if (!inOutMode.is_open())
    {
        std::cout << "Failed save \"" << currFileName << "\".\n";
        return;
    }

    FileWriter::saveTheaterData(theater, inOutMode);
    std::cout << "Successfully saved \"" << currFileName << "\".\n";

    inOutMode.close();
}

void Engine::saveAs(string& filePath) {                 
    string fileName = checkFileName(filePath);
    if (fileName == "")
    {
        return;
    }

    fstream newFile(fileName, std::ios::out);
    if (!newFile.is_open())
    {
        std::cout << "Failed to open and save \"" << fileName << "\".\n";
        return;
    }
    
    FileWriter::saveTheaterData(theater, newFile);
    std::cout << "Successfully saved \"" << fileName << "\".\n";

    newFile.close();   
}