/*
 * display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#pragma once

#include <memory>
#include <string>
#include <zge/defines.h>
#include <zge/noncopyable.h>

BEGIN_ZGE_NAMESPACE

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

typedef std::shared_ptr<class ZDisplay> ZDisplayRef;

class ZDisplay : public ZNoncopyable, public std::enable_shared_from_this<ZDisplay> {
    std::auto_ptr<struct ZDisplayImpl> _impl;
    
protected:
    bool _initialized;
    ZDisplayMode _display_mode;
    uint32_t _last_render;
    bool _captures_input;
    
protected: // Only a display manager can create displays
    ZDisplay() = default;
    ZDisplay(const ZDisplayMode &display_mode);
    
public:
    virtual ~ZDisplay();
    
    void initialize();
    void update(uint32_t dtime);
    
    // Convenience method for setting width/height values in the current display mode
    void resize(int width, int height);
    
    /* Accessors */
    bool is_initialized() { return _initialized; }
    bool captures_input() const { return _captures_input; }
    void set_captures_input(bool capture);
    
    ZDisplayMode get_display_mode() { return _display_mode; }
    void set_display_mode(const ZDisplayMode &mode);
    
    /* Swapping the OpenGL Buffer */
    void swap_buffer();
    
    /* Friends */
    friend class ZDisplayManager;
    friend class ZRenderContext;
    
protected:
    void  _init_window();
    void* _get_sdl_window();
};

END_ZGE_NAMESPACE
