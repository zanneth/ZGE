/*
 * gl_display.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/09/2012
 */
 
#pragma once

#include "zge/display.h"
#include "zge/noncopyable.h"

#include <SDL/SDL.h>
#include <string>

namespace zge {

class ZGLDisplay : public ZDisplay, ZNoncopyable {
    SDL_Surface *_surface;
    uint32_t _last_render;
    
public:
    ZGLDisplay();
    ZGLDisplay(const ZDisplayMode &mode);
    ~ZGLDisplay();
    
    /** Overrides **/
    void initialize() override;
    void render(uint32_t dtime) override;
    
    void set_display_mode(const ZDisplayMode &mode) override;
    
private:
    void _load_surface();
    void _init_glew();
    void _init_opengl();
    
    void _change_window_title(std::string new_title);
};

} // namespace zge
