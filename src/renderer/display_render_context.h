/*
 * display_render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/render_context.h>

ZGE_BEGIN_NAMESPACE

class ZDisplayRenderContext : public ZRenderContext {
public:
    ZDisplayRenderContext(ZDisplayRef display);
    ~ZDisplayRenderContext();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZDisplayRenderContext);
    
    ZDisplayRef get_display() const;
    void make_current() override;
    
private:
    std::unique_ptr<struct ZDisplayRenderContextImpl> _impl;
};

ZGE_DEFINE_SREF_TYPE(ZDisplayRenderContext);

ZGE_END_NAMESPACE
