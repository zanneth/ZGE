//
//  gl_display.h
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#ifndef _ZGE_GL_DISPLAY_H_
#define _ZGE_GL_DISPLAY_H_

#include <SDL/SDL.h>
#include <zge/graphics/display.h>


namespace zge {

class ZGLDisplay : public ZDisplay {
    SDL_Surface *_surface;
    
public:
    ~ZGLDisplay();
    
    /** Accessors **/
    SDL_Surface* getSurface() { return _surface; }
    void setSurface(SDL_Surface *surface) { _surface = surface; }
    
    
    /** Overrides **/
    void initialize();
    void render();
    
    ZError setDisplayMode(const ZDisplayMode &mode);
    ZError setCoordinateSystem(const ZCoordinateSystem &coordSystem);
    
private:
    void _initOpenGL();
};

}

#endif // _ZGE_GL_DISPLAY_H_
