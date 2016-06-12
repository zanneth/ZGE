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

ZGE_BEGIN_NAMESPACE

struct ZDisplayMode {
    bool        windowed;
    unsigned    width;
    unsigned    height;
    float       scale;
    std::string window_title;
    
public:
    ZDisplayMode() :
        windowed(true),
        width(1024),
        height(768),
        scale(1.0),
        window_title("Application") {}
};

typedef std::shared_ptr<class ZDisplay> ZDisplayRef;

class ZDisplay : public ZNoncopyable {
protected: // Only a render manager can create displays
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
    
    ZDisplayMode get_display_mode() { return _display_mode; }
    void set_display_mode(const ZDisplayMode &mode);
    
    /* Swapping the OpenGL Buffer */
    void swap_buffer();
    
    /* Friends */
    friend class ZDisplayRenderContext;
    friend class ZRenderManager;
    
protected:
    void  _init_window();
    void* _get_sdl_window();
    
private:
    std::auto_ptr<struct ZDisplayImpl> _impl;
    
protected:
    bool _initialized;
    ZDisplayMode _display_mode;
    bool _captures_input;
};

ZGE_END_NAMESPACE
