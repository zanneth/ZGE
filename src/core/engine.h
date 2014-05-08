/*
 * engine.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#pragma once

#include <zge/defines.h>
#include <zge/audio_manager.h>
#include <zge/display_manager.h>
#include <zge/input_manager.h>
#include <zge/noncopyable.h>
#include <zge/render_manager.h>
#include <zge/types.h>

BEGIN_ZGE_NAMESPACE

class ZEngine : ZNoncopyable {
    ZInputManagerRef    _input_manager;
    ZRenderManagerRef   _render_manager;
    ZDisplayManagerRef  _display_manager;
    ZAudioManagerRef    _audio_manager;
    
    ZResponderRef       _application_responder;

public:
    static ZEngine* instance();
    
    /* Accessors */
    ZInputManagerRef    get_input_manager();
    ZRenderManagerRef   get_render_manager();
    ZDisplayManagerRef  get_display_manager();
    ZAudioManagerRef    get_audio_manager();
    
    /* Utility */
    ZRect get_viewport_rect() const;
    
    /* Initialization */
    void initialize();
    
private:
    // singleton
    ZEngine();
};

END_ZGE_NAMESPACE
