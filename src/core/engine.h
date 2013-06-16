/*
 * engine.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/07/2012
 */
 
#pragma once

#include <zge/display_manager.h>
#include <zge/scene_manager.h>
#include <zge/geometry.h>
#include <zge/input_manager.h>
#include <zge/noncopyable.h>
#include <zge/render_manager.h>

namespace zge {

class ZEngine : ZNoncopyable {
    ZInputManagerRef    _input_manager;
    ZSceneManagerRef    _scene_manager;
    ZRenderManagerRef   _render_manager;
    ZDisplayManagerRef  _display_manager;
    
    ZResponderRef       _application_responder;

public:
    static ZEngine* instance();
    
    /* Accessors */
    ZInputManagerRef    get_input_manager()   { return _input_manager; }
    ZSceneManagerRef    get_scene_manager()   { return _scene_manager; }
    ZRenderManagerRef   get_render_manager()  { return _render_manager; }
    ZDisplayManagerRef  get_display_manager() { return _display_manager; }
    
    /* Utility */
    AlignedBox2f get_viewport_rect() const;
    
    /* Initialization */
    void initialize();
    
private:
    // singleton
    ZEngine();
};

} // namespace zge
