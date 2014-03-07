/*
 * exception.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <exception>
#include <string>
#include <zge/defines.h>

BEGIN_ZGE_NAMESPACE

enum {
    ZUNKNOWN_EXCEPTION_CODE              = -1,
    ZNOT_IMPLEMENTED_EXCEPTION_CODE      = 100,
    ZAPPLICATION_EXCEPTION_CODE          = 200,
    ZDISPLAY_EXCEPTION_CODE              = 300,
    ZENGINE_EXCEPTION_CODE               = 400,
    ZMATHEMATIC_EXCEPTION_CODE           = 500,
    ZFILE_EXCEPTION_CODE                 = 600,
    ZASSERTION_EXCEPTION_CODE            = 700
};

struct ZException : public std::exception {
    int code;
    std::string description;
    std::string extra_info;
    
    ZException(int code_ = ZUNKNOWN_EXCEPTION_CODE);
    
    virtual const char* what() const throw();
    
    bool operator==(const ZException &other);
    bool operator!=(const ZException &other);
};

END_ZGE_NAMESPACE
