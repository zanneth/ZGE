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
    unsigned _lastRender;
    
public:
    ~ZGLDisplay();    
    
    /** Overrides **/
    void initialize();
    void render(unsigned dtime);
    
    ZError setDisplayMode(const ZDisplayMode &mode);
    ZError setCoordinateSystem(const ZCoordinateSystem &coordSystem);
    
private:
    void _initOpenGL();
    void _reloadViewport();
    void _reloadCoordinateSystem();
};

}

#endif // _ZGE_GL_DISPLAY_H_
