/*
 * application.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include <zge/event.h>
#include <zge/noncopyable.h>
#include <zge/run_loop.h>

#include <string>
#include <vector>

BEGIN_ZGE_NAMESPACE

class ZApplication : ZNoncopyable {
    std::vector<std::string> _arguments;
    bool _show_cursor;
    
    ZRunloop _main_runloop;
    uint32_t _time_start;
    
public:
    ZApplication(int argc, const char **argv);
    virtual ~ZApplication();
    
    /* Getting the Application Instance */
    static ZApplication* get_current_application();
    
    /* Running */
    void run();
    
    /* Accessors */
    std::vector<std::string> get_arguments() { return _arguments; }
    void set_arguments(int argc, const char **argv);
    bool shows_cursor() { return _show_cursor; }
    void set_shows_cursor(bool cursor) { _show_cursor = cursor; }
    
    /* Accessing the Main Run Loop */
    ZRunloop* get_main_runloop();
    void start_main_runloop();
    
    /* Utility Functions */
    uint32_t get_time_running(); // returns time in seconds
    void exit();
    
    /* Handling Events */
    // the engine is responsible for pushing events to the application instance since
    // it is the owner of the input manager
    virtual void handle_application_event(const ZEvent &event);
    
    /* Callbacks */
    virtual void application_ready() {}

private:
    void _change_resources_directory();
};

END_ZGE_NAMESPACE
