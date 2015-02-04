/*
 * engine.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/audio_manager.h>
#include <zge/input_manager.h>
#include <zge/noncopyable.h>
#include <zge/render_manager.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZEngine : ZNoncopyable {
public:
    ZEngine();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZEngine);
    
    /* Accessors */
    ZInputManagerRef    get_input_manager();
    ZRenderManagerRef   get_render_manager();
    ZAudioManagerRef    get_audio_manager();
    
    /* Utility */
    ZRect get_viewport_rect() const;
    
    // convenience: accesses the render manager's scene property
    ZSceneRef get_current_scene() const;
    void set_current_scene(ZSceneRef scene);
    
    /* Initialization */
    void initialize();
    
private:
    ZInputManagerRef  _input_manager;
    ZRenderManagerRef _render_manager;
    ZAudioManagerRef  _audio_manager;
    
    ZResponderRef     _application_responder;
};

ZGE_DEFINE_SREF_TYPE(ZEngine);

ZGE_END_NAMESPACE
