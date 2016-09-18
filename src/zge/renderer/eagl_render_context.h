/*
 * eagl_render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#pragma once

#include <zge/core/foundation.h>
#include <zge/renderer/render_context.h>

#ifdef __OBJC__
@class EAGLContext;
#else
using EAGLContext = void;
#endif

ZGE_BEGIN_NAMESPACE

enum ZEAGLRenderingAPI {
    ZEAGL_RENDERING_API_OPENGLES1,
    ZEAGL_RENDERING_API_OPENGLES2,
    ZEAGL_RENDERING_API_OPENGLES3
};

class ZEAGLRenderContext : public ZRenderContext {
public:
    ZEAGLRenderContext(ZEAGLRenderingAPI api = ZEAGL_RENDERING_API_OPENGLES3);
    ZEAGLRenderContext(EAGLContext *context);
    ~ZEAGLRenderContext();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZEAGLRenderContext);
    
    EAGLContext* get_eagl_context() const;
    void make_current() override;

private:
    unsigned _eagl_api_from_zrendering_api(ZEAGLRenderingAPI zapi);

private:
    EAGLContext *_eagl_context;
};

ZGE_DEFINE_SREF_TYPE(ZEAGLRenderContext);

ZGE_END_NAMESPACE
