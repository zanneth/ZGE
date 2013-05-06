/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <SDL2/SDL.h>
#include <zge/noncopyable.h>
#include <string>

namespace zge {

struct ZDisplayMode {
    bool windowed;
    unsigned width;
    unsigned height;
    float refresh_rate;
    std::string window_title;
    
public:
    ZDisplayMode() :
        windowed(true),
        width(1024),
        height(768),
        refresh_rate(1.0f / 60.0f),
        window_title("Application") {}
};

class ZDisplay : ZNoncopyable {
protected:
    bool _initialized;
    ZDisplayMode _display_mode;
    
    SDL_Window *_window;
    SDL_GLContext _context;
    uint32_t _last_render;
    
protected: // Only a display manager can create displays
    ZDisplay() = default;
    ZDisplay(const ZDisplayMode &display_mode);
    
public:
    void initialize();
    void update(uint32_t dtime);
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    /** Accessors **/
    bool is_initialized() { return _initialized; }
    
    ZDisplayMode get_display_mode() { return _display_mode; }
    void set_display_mode(const ZDisplayMode &mode);
    
    /** Friends **/
    friend class ZDisplayManager;
    
protected:
    void _init_window();
    void _init_opengl();
};

} // namespace zge
