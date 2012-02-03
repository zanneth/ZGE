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

enum {
    kUnknownError   = -1,
    kNoError        = 0
};

using std::string;

class ZError {
    int _code;
    string _description;
    
public:
    ZError();
    ZError(int code, string description);
    
    static ZError noError();
    
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