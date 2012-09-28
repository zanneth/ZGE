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

enum {
    UNKNOWN_EXCEPTION_CODE = -1,
    NOT_IMPLEMENTED_EXCEPTION_CODE,
    APPLICATION_EXCEPTION_CODE,
    DISPLAY_EXCEPTION_CODE,
    ENGINE_EXCEPTION_CODE,
    MATHEMATIC_EXCEPTION_CODE
};

class ZException : public std::exception {
public:
    int code;
    std::string description;
    std::string extra_info;
    
    ZException(int code_ = UNKNOWN_EXCEPTION_CODE);
    
    virtual const char* what() const throw();
    
    bool operator==(const ZException &other);
    bool operator!=(const ZException &other);
};

} // namespace zge
