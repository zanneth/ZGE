/*
 * render_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <zge/defines.h>
#include <zge/display.h>
#include <zge/noncopyable.h>
#include <zge/render_context.h>
#include <zge/scene.h>
#include <zge/schedulable.h>
#include <zge/types.h>

BEGIN_ZGE_NAMESPACE

class ZRenderManager : public ZSchedulable, ZNoncopyable {
public:
    ZRenderManager();
    ~ZRenderManager();
    
    /// Creates a new display and sets as current.
    ZDisplayRef create_display(const ZDisplayMode &mode);
    ZDisplayRef get_current_display() const;
    
    /* Accessors */
    ZRenderContextRef get_context() const;
    
    ZSceneRef get_scene() const;
    void set_scene(ZSceneRef scene);
    
    /* Schedulable Overrides */
    void run(uint32_t dtime) override;
    
private:
    void _initialize_render_context();
    
private:
    ZDisplayRef _display;
    ZRenderContextRef _context;
    ZSceneRef _scene;
    bool _initialized;
};

typedef std::shared_ptr<ZRenderManager> ZRenderManagerRef;

END_ZGE_NAMESPACE
