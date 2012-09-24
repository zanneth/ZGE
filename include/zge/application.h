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

class platform;
class runloop;

class application : noncopyable {
    std::list<std::string> _arguments;
    platform *_current_platform; // weak
    unsigned _time_start;
    
public:
    application(int argc, char **argv);
    virtual ~application();
    
    /** Accessors **/
    std::list<std::string> get_arguments() { return _arguments; }
    void set_arguments(int argc, char **argv);
    platform* get_current_platform() { return _current_platform; }
    
    /** Accessing the Main Run Loop **/
    static runloop* get_main_runloop();
    void start_main_runloop();
    
    /** Utility Functions **/
    unsigned get_secs_running();
    
    /** Callbacks **/
    virtual void application_ready() {}
    
    /** Running (external) **/
    friend void run_application(application*);
};

void run_application(application *application);

} // namespace zge
