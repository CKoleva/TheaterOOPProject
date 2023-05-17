#pragma once
#include <fstream>
#include <iostream>
#include <Theater.h>

class FileReader {
public:
   static void loadTheaterData(Theater& theater, const std::string& filename);
};

