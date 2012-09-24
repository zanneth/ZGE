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

class uid {
    unsigned _uidnum;

public:
    uid() :
        _uidnum(std::rand())
    {}
    
    bool operator==(const uid &other) const
    {
        return _uidnum == other._uidnum;
    }
    
    bool operator!=(const uid &other) const
    {
        return !operator==(other);
    }
    
    std::string get_description() const
    {
        std::ostringstream oss;
        oss << _uidnum;
        return oss.str();
    }
};

template <class T>
struct nulldeleter {
    void operator()(void const *) {}
};

} // namespace zge
