/*
 * exception.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <exception>

namespace zge {

enum {
    UNKNOWN_EXCEPTION_CODE              = -1,
    NOT_IMPLEMENTED_EXCEPTION_CODE      = 100,
    APPLICATION_EXCEPTION_CODE          = 200,
    DISPLAY_EXCEPTION_CODE              = 300,
    ENGINE_EXCEPTION_CODE               = 400,
    MATHEMATIC_EXCEPTION_CODE           = 500,
    FILE_EXCEPTION_CODE                 = 600,
    ASSERTION_EXCEPTION_CODE            = 700
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
