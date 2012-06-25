/*
 * application.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/noncopyable.h"

#include <list>
#include <memory>
#include <string>

namespace zge {

class ZPlatform;
class ZRunLoop;

class ZApplication : ZNonCopyable {
    std::list<std::string> _arguments;
    ZPlatform *_currentPlatform;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication() = default;
    
    /** Accessors **/
    std::list<std::string> getArguments() const { return _arguments; }
    void setArguments(int argc, char **argv);
    ZPlatform* getCurrentPlatform() const { return _currentPlatform; }
    
    /** Accessing the Main Run Loop **/
    static ZRunLoop* getMainRunLoop();
    void startMainRunLoop();
    
    /** Callbacks **/
    virtual void applicationReady() {}
    
    /** Running (external) **/
    friend void runApplication(ZApplication*);
};

void runApplication(ZApplication *application);

} // namespace zge
