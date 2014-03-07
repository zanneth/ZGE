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
    ZRenderContextRef _context;
    ZSceneRef _scene;
    bool _initialized;
    
public:
    ZRenderManager();
    ~ZRenderManager();
    
    /* Accessors */
    ZRenderContextRef get_context() const;
    
    ZSceneRef get_scene() const;
    void set_scene(ZSceneRef scene);
    
    /* Schedulable Overrides */
    void run(uint32_t dtime) override;
    
protected:
    void _setup_display(ZDisplayRef display);
    friend class ZDisplayManager;
    
private:
    void _initialize();
};

typedef std::shared_ptr<ZRenderManager> ZRenderManagerRef;

END_ZGE_NAMESPACE
