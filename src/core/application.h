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

#include <list>
#include <string>

namespace zge {

class ZApplication : ZNoncopyable {
    std::list<std::string> _arguments;
    bool _show_cursor;
    bool _capture_input;
    
    ZRunloop _main_runloop;
    uint32_t _time_start;
    
public:
    ZApplication(int argc, char **argv);
    virtual ~ZApplication();
    
    /** Getting the Application Instance **/
    static ZApplication* get_current_application();
    
    /** Running **/
    void run();
    
    /** Accessors **/
    std::list<std::string> get_arguments() { return _arguments; }
    void set_arguments(int argc, char **argv);
    bool shows_cursor() { return _show_cursor; }
    void set_shows_cursor(bool cursor) { _show_cursor = cursor; }
    bool captures_input() { return _capture_input; }
    void set_captures_input(bool capture) { _capture_input = capture; }
    
    /** Accessing the Main Run Loop **/
    ZRunloop* get_main_runloop();
    void start_main_runloop();
    
    /** Utility Functions **/
    uint32_t get_time_running(); // returns time in seconds
    void exit();
    
    /** Handling Events **/
    // the engine is responsible for pushing events to the application instance since
    // it is the owner of the input manager
    virtual void handle_application_event(const ZEvent &event);
    
    /** Callbacks **/
    virtual void application_ready() {}

private:
    void _change_resources_directory();
};

} // namespace zge
