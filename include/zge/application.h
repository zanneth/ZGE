/*
 * application.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <list>

namespace zge {

class ZPlatform;
class ZRunloop;

class ZApplication : ZNoncopyable {
    std::list<std::string> _arguments;
    ZPlatform *_current_platform; // weak
    unsigned _time_start;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication();
    
    /** Accessors **/
    std::list<std::string> get_arguments() { return _arguments; }
    void set_arguments(int argc, char **argv);
    ZPlatform* get_current_platform() { return _current_platform; }
    
    /** Accessing the Main Run Loop **/
    static ZRunloop* get_main_runloop();
    void start_main_runloop();
    
    /** Utility Functions **/
    unsigned get_secs_running();
    
    /** Callbacks **/
    virtual void application_ready() {}
    
    /** Running (external) **/
    friend void run_application(ZApplication*);
};

void run_application(ZApplication *application);

} // namespace zge
