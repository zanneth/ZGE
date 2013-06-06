/*
 * render_manager.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 05/19/2013
 */

#pragma once

#include <memory>
#include <zge/noncopyable.h>
#include <zge/render_context.h>
#include <zge/schedulable.h>
#include <zge/types.h>

namespace zge {

class ZRenderManager : public ZSchedulable, ZNoncopyable {
    ZRenderContextRef _context;
    bool _initialized;
    
public:
    ZRenderManager();
    ~ZRenderManager();
    
    /* Schedulable Overrides */
    void run(uint32_t dtime) override;
    
private:
    void _initialize();
};

typedef std::shared_ptr<ZRenderManager> ZRenderManagerRef;

} // namespace zge
