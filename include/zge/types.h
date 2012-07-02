/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <cstdlib>
#include <string>

namespace zge {

class ZUUID {
    unsigned _uuidnum;

public:
    ZUUID() :
        _uuidnum(std::rand())
    {}
    
    bool operator==(const ZUUID &other)
    {
        return _uuidnum == other._uuidnum;
    }
    
    bool operator!=(const ZUUID &other)
    {
        return !operator==(other);
    }
    
    std::string getDescription()
    {
        char str[11];
        sprintf(str, "%010d", _uuidnum);
        return str;
    }
};

template <class T>
struct ZNullDeleter {
    void operator()(void const *) {}
};

} // namespace zge
