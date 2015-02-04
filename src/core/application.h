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

ZGE_BEGIN_NAMESPACE

class ZApplication : ZNoncopyable {
public:
    ZApplication(int argc, const char **argv);
    virtual ~ZApplication();
    
    /// Initializes the application and starts the main runloop. (Does not return.)
    void run();
    
    /// Return an array of program arguments provided to the app.
    std::vector<std::string> get_arguments();
    
    /// Returns true if the mouse cursor is allowed to be shown when this
    /// application is active.
    bool shows_cursor() const;
    
    /// Sets whether or not the cursor should be allowed to be visible when this
    /// application is active.
    void set_shows_cursor(bool cursor);
    
    /// Returns true if the mouse cursor should behave 'relatively', meaning
    /// movements should be tracked as deltas instead of absolute positioning on
    /// the screen.
    bool get_use_relative_cursor() const;
    
    /// Sets whether or not the cursor should behave relatively. When true, the
    /// application will treat cursor movement differentially rather than
    /// tracking absolute positioning.
    void set_use_relative_cursor(bool use_relative);
    
    /// Returns the main runloop for the application.
    ZRunloopRef get_main_runloop();
    
    /// Returns the amount of time that this application has been running.
    ZTimeInterval get_time_running();
    
    /// Asks the main runloop to stop and relinquishes control flow from the
    /// application.
    void exit();
    
    /* Handling Events */
    // the engine is responsible for pushing events to the application instance since
    // it is the owner of the input manager
    virtual void handle_application_event(const ZEvent &event);
    
    /* Callbacks */
    virtual void application_ready() {}
    
private:
    std::vector<std::string> _arguments;
    ZRunloopRef _main_runloop;
    bool        _show_cursor;
    bool        _use_relative_cursor;
    ZTime       _time_start;
};

ZGE_END_NAMESPACE
