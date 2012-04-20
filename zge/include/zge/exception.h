/*
 * exception.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <exception>
#include <string>

namespace zge {

class ZException : public std::exception {
public:
    std::string description;
    
    virtual const char* what() const throw()
    {
        std::string err = "An exception occurred: " + description;
        return err.c_str();
    }
};

} // namespace zge
