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
#include <zge/thread.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZRenderManager : public ZSchedulable,
                       public ZNoncopyable,
                       public std::enable_shared_from_this<ZRenderManager>
{
public:
    ZRenderManager();
    ~ZRenderManager();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZRenderManager);
    
    /* Accessors */
    ZDisplayRef get_current_display() const;
    ZRenderContextRef get_context() const;
    
    ZSceneRef get_scene() const;
    void set_scene(ZSceneRef scene);
    
    /* API */
    
    /// Creates a new display and sets as current.
    ZDisplayRef create_display(const ZDisplayMode &mode);
    
    /// Starts the render manager.
    void start();
    
    /* Schedulable Overrides */
    void run(uint32_t dtime) override;
    
private:
    void _initialize_render_context();
    
private:
    ZDisplayRef _display;
    ZRenderContextRef _context;
    ZSceneRef _scene;
    ZThreadRef _thread;
    bool _initialized;
};

ZGE_DEFINE_SREF_TYPE(ZRenderManager);

ZGE_END_NAMESPACE
