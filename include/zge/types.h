/*
 * types.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <cstdlib>
#include <sstream>
#include <string>

namespace zge {

class ZUUID {
    unsigned _uuidnum;

public:
    ZUUID() :
        _uuidnum(std::rand())
    {}
    
    bool operator==(const ZUUID &other) const
    {
        return _uuidnum == other._uuidnum;
    }
    
    bool operator!=(const ZUUID &other) const
    {
        return !operator==(other);
    }
    
    std::string getDescription() const
    {
        std::ostringstream oss;
        oss << _uuidnum;
        return oss.str();
    }
};

template <class T>
struct ZNullDeleter {
    void operator()(void const *) {}
};

} // namespace zge
