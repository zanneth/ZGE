/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include "zge/noncopyable.h"
#include <string>

namespace zge {

struct display_mode {
    bool windowed;
    unsigned width;
    unsigned height;
    float refresh_rate;
    std::string window_title;
    
public:
    display_mode() :
        windowed(true),
        width(1024),
        height(768),
        refresh_rate(1.0f / 60.0f),
        window_title("Application") {}
};

class display : noncopyable {
protected:
    bool _is_initialized;
    display_mode _display_mode;

protected: // Only a display manager can create displays
    display() = default;
    display(const display_mode &display_mode);
    
public:
    virtual ~display() {}
    
    /** Initialization **/
    virtual void initialize() = 0;
    
    /** Rendering **/
    virtual void render(unsigned dtime) = 0;
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    /** Accessors **/
    bool is_initialized() { return _is_initialized; }
    
    display_mode get_display_mode() { return _display_mode; }
    virtual void set_display_mode(const display_mode &mode);
    
    /** Friends **/
    friend class display_manager;
};

} // namespace zge
