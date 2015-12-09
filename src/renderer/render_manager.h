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
#include <zge/renderable.h>
#include <zge/schedulable.h>
#include <zge/thread.h>
#include <zge/types.h>

ZGE_BEGIN_NAMESPACE

class ZRenderManager : public ZNoncopyable, public ZSchedulable {
public:
    ZRenderManager();
    ~ZRenderManager();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZRenderManager);
    
    /// Creates a new display and sets as current.
    ZDisplayRef create_display(const ZDisplayMode &mode);
    
    /// Returns the display that is being managed by this render manager.
    ZDisplayRef get_current_display() const;
    
    /// Returns the render context being used by this render manager.
    ZRenderContextRef get_context() const;
    
    /// Returns the current renderable object being used.
    ZRenderableRef get_renderable() const;
    
    /// Sets the object to be rendered.
    void set_renderable(ZRenderableRef renderable);
    
    /// Schedulable override.
    void run(uint32_t dtime) override;
    
private:
    void _initialize_render_context();
    void _run(uint32_t dtime);
    
private:
    ZDisplayRef         _display;
    ZRenderContextRef   _context;
    ZRenderableRef      _renderable;
    ZTime               _last_frame_drawn;
    bool                _initialized;
};

ZGE_DEFINE_SREF_TYPE(ZRenderManager);

ZGE_END_NAMESPACE
