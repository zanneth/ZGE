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
    int code;
    std::string description;
    std::string extra_info;
    
    ZException(int code_ = -1, std::string description_ = "Unknown Description");
    
    virtual const char* what() const throw();
    
    bool operator==(const ZException &other)
    {
        return code == other.code;
    }
    
    bool operator!=(const ZException &other)
    {
        return !operator==(other);
    }
};

class ZNotImplementedException : public ZException {
public:
    ZNotImplementedException() : ZException(
        10,
        "Functionality not yet implemented."
    ) {}
};

class ZApplicationException : public ZException {
public:
    ZApplicationException() : ZException(
        100,
        "The application failed to initialize."
    ) {}
};

class ZDisplayException : public ZException {
public:
    ZDisplayException() : ZException(
        200,
        "The display failed to initialize."
    ) {}
};

class ZEngineException : public ZException {
public:
    ZEngineException() : ZException(
        300,
        "The engine failed to initialize."
    ) {}
};

class ZMathematicException : public ZException {
public:
    ZMathematicException() : ZException(
        400,
        "Mathematic exception."
    ) {}
};

} // namespace zge
