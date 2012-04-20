/*
 * error.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <string>

namespace zge {

enum {
    kUnknownError   = -1,
    kNoError        = 0
};

class ZError {
    int _code;
    std::string _description;
    
public:
    ZError();
    ZError(int code, std::string description);
    
    static ZError noError();
    
    /** Operators **/
    bool operator==(const ZError &other);
    bool operator!=(const ZError &other);
    
    
    /** Accessors **/
    int getCode() const { return _code; }
    void setCode(const int code) { _code = code; }
    std::string getDescription() const { return _description; }
    void setDescription(const std::string description) { _description = description; }
};

} // namespace zge
