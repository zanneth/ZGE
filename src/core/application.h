/*
 * application.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/event.h>
#include <zge/noncopyable.h>
#include <zge/run_loop.h>

#include <string>
#include <vector>

BEGIN_ZGE_NAMESPACE

class ZApplication : ZNoncopyable {
    std::vector<std::string> _arguments;
    bool _show_cursor;
    bool _use_relative_cursor;
    
    ZRunloop _main_runloop;
    ZTime _time_start;
    
public:
    ZApplication(int argc, const char **argv);
    virtual ~ZApplication();
    
    /* Getting the Application Instance */
    static ZApplication* get_current_application();
    
    /* Running */
    void run();
    
    /* Accessors */
    std::vector<std::string> get_arguments();
    void set_arguments(int argc, const char **argv);
    
    bool shows_cursor() const;
    void set_shows_cursor(bool cursor);
    
    bool get_use_relative_cursor() const;
    void set_use_relative_cursor(bool use_relative);
    
    /* Accessing the Main Run Loop */
    ZRunloop* get_main_runloop();
    void start_main_runloop();
    
    /* Utility Functions */
    ZTimeInterval get_time_running();
    void exit();
    
    /* Handling Events */
    // the engine is responsible for pushing events to the application instance since
    // it is the owner of the input manager
    virtual void handle_application_event(const ZEvent &event);
    
    /* Callbacks */
    virtual void application_ready() {}
};

END_ZGE_NAMESPACE
