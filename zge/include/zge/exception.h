//
//  exception.h
//  ZGE
//
//  Created by Charles Magahern on 2/3/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include <exception>
#include <string>

namespace zge {

using std::string;

class ZException : public std::exception {
public:
    string description;
    
    virtual const char* what() const throw()
    {
        string err = "An exception occurred: " + description;
        return err.c_str();
    }
};

} // namespace zge