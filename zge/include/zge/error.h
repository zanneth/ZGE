//
//  error.h
//  ZGE
//
//  Created by Charles Magahern on 1/13/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#pragma once

#include <string>

namespace zge {
using std::string;

enum {
    kUnknownError       = -1,
    kNoError            = 0,
    kApplicationError   = 1,
    kSDLError           = 2,
    kDisplayInitError   = 3
};

class ZError {
    int _code;
    string _description;
    
public:
    ZError();
    ZError(int code, string description);
    
    static ZError NoError();
    
    /** Operators **/
    bool operator==(const ZError &other);
    bool operator!=(const ZError &other);
    
    
    /** Accessors **/
    int getCode() const { return _code; }
    void setCode(const int code) { _code = code; }
    string getDescription() const { return _description; }
    void setDescription(const string description) { _description = description; }
};

} // namespace zge