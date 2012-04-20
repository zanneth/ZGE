/*
 * application.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/run_loop.h"
#include "zge/exception.h"
#include "zge/noncopyable.h"

#include <string>
#include <list>
#include <memory>

namespace zge {

class ZApplicationException : public ZException {
public:
    virtual const char* what() const throw()
    {
        return ("An application error occurred: " + description).c_str();
    }
};

class ZApplication : private ZNonCopyable {
    std::list<std::string> _arguments;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() = default;
    
    /** Accessors **/
    std::list<std::string> getArguments() const { return _arguments; }
    void setArguments(int argc, char **argv);
    
    
    /** Accessing the Main Run Loop **/
    static ZRunLoop* getMainRunLoop();
    void startMainRunLoop();
    
    
    /** Callbacks **/
    virtual void applicationReady() {}
};

void runApplication(ZApplication *application);

} // namespace zge
