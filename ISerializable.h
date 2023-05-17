#pragma once
#include <string>
#include <sstream>

using std::stringstream;
using std::string;

//interface
class ISerializable {
public:
    virtual const string serialize() const = 0;
    virtual void deserialize(const string& data) = 0;
};