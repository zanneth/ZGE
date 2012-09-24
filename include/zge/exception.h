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

class exception : public std::exception {
public:
    int code;
    std::string description;
    std::string extra_info;
    
    exception(int code_ = -1, std::string description_ = "Unknown Description");
    
    virtual const char* what() const throw();
    
    bool operator==(const exception &other)
    {
        return code == other.code;
    }
    
    bool operator!=(const exception &other)
    {
        return !operator==(other);
    }
};

class not_implemented_exception : public exception {
public:
    not_implemented_exception() : exception(
        10,
        "Functionality not yet implemented."
    ) {}
};

class application_exception : public exception {
public:
    application_exception() : exception(
        100,
        "The application failed to initialize."
    ) {}
};

class display_exception : public exception {
public:
    display_exception() : exception(
        200,
        "The display failed to initialize."
    ) {}
};

class engine_exception : public exception {
public:
    engine_exception() : exception(
        300,
        "The engine failed to initialize."
    ) {}
};

class mathematic_exception : public exception {
public:
    mathematic_exception() : exception(
        400,
        "Mathematic exception."
    ) {}
};

} // namespace zge
