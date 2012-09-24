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

class gldisplay : public display, noncopyable {
    SDL_Surface *_surface;
    unsigned _last_render;
    
public:
    gldisplay();
    gldisplay(const display_mode &mode);
    ~gldisplay();
    
    /** Overrides **/
    void initialize() override;
    void render(unsigned dtime) override;
    
    void set_display_mode(const display_mode &mode) override;
    
private:
    void _load_surface();
    void _init_opengl();
    
    void _change_window_title(std::string new_title);
};

} // namespace zge
