#pragma once
#include <string>
#include <cstddef>

using std::string;
using std::size_t;

class Venue {
protected:
    string name;
public:
    Venue(const string& name);

    //Getter
    const string& getName() const;
    
    virtual ~Venue() = default;
};