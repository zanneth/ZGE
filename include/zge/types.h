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

class ZUID {
    unsigned _uidnum;

public:
    ZUID() :
        _uidnum(std::rand())
    {}
    
    bool operator==(const ZUID &other) const
    {
        return _uidnum == other._uidnum;
    }
    
    bool operator!=(const ZUID &other) const
    {
        return !operator==(other);
    }
    
    std::string getDescription() const
    {
        std::ostringstream oss;
        oss << _uidnum;
        return oss.str();
    }
};

template <class T>
struct ZNullDeleter {
    void operator()(void const *) {}
};

} // namespace zge
