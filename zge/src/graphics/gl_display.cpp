//
//  gl_display.cpp
//  ZGE
//
//  Created by Charles Magahern on 1/4/12.
//  Copyright (c) 2012 omegaHern. All rights reserved.
//

#include "gl_display.h"

#include <iostream>
#include <string>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>

#include <zge/util/logger.h>
#include <zge/util/util.h>


namespace zge {

ZGLDisplay::~ZGLDisplay()
{
    if (_surface != NULL) {
        SDL_FreeSurface(_surface);
        _surface = NULL;
    }
}


#pragma mark - Initialization

void ZGLDisplay::initialize()
{
    if (!_isInitialized) {
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);     // Request 16-bit depth
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);    // Request double-buffering
        
        Uint32 sdlFlags = 0;
        sdlFlags |= SDL_OPENGL;
        
        if (!_displayMode.windowed) {
            sdlFlags |= SDL_FULLSCREEN;
        }
        
        _surface = SDL_SetVideoMode(_displayMode.width, _displayMode.height, 0, sdlFlags);
        if (!_surface) {
            std::string errorStr = "The OpenGL display surface failed to initialize: ";
            errorStr += SDL_GetError();
            
            ZError err(ZGE_DISPLAY_INIT_ERROR, errorStr);
            util::fatalError(err);
        }
        
        const char *windowName = _displayMode.windowTitle.c_str();
        SDL_WM_SetCaption(windowName, windowName);
        
        _isInitialized = true;
    } else {
        LOGGER->debugLog("Warning: Display already initialized.");
    }
}


#pragma mark - Rendering

void ZGLDisplay::render()
{
    SDL_GL_SwapBuffers();
}


#pragma mark - Changing Properties

ZError ZGLDisplay::setDisplayMode(const ZDisplayMode &mode)
{
    if (mode.width != _displayMode.width || mode.height != _displayMode.height) {
        glViewport(0, 0, mode.width, mode.height);
    }
    
    return ZDisplay::setDisplayMode(mode);
}

ZError ZGLDisplay::setCoordinateSystem(const ZCoordinateSystem &coordSystem)
{
    if (_coordinateSystem != coordSystem) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        if ((ZCoordinateSystem) coordSystem == ZCoordinateSystemZero) {
            glOrtho(0, 1024, 0, 768, -512, 512);
        } else {
            glOrtho(0,
                    coordSystem.width,
                    0,
                    coordSystem.height,
                    -coordSystem.depth,
                    coordSystem.depth);
        }
        
        glMatrixMode(GL_MODELVIEW);
    }
        
    return ZDisplay::setCoordinateSystem(coordSystem);
}


#pragma mark - Private Methods

void ZGLDisplay::_initOpenGL()
{
    glClearColor(0.0, 0.0, 0.0, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}
