/*
 * eagl_render_context.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#pragma once

#include <zge/foundation.h>
#include <zge/render_context.h>

#ifdef __OBJC__
@class EAGLContext;
#else
using EAGLContext = void;
#endif

ZGE_BEGIN_NAMESPACE

class ZEAGLRenderContext : public ZRenderContext {
public:
    ZEAGLRenderContext();
    ~ZEAGLRenderContext();
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZEAGLRenderContext);
    
    EAGLContext* get_eagl_context() const;
    void make_current() override;
    
private:
    EAGLContext *_eagl_context;
};

ZGE_DEFINE_SREF_TYPE(ZEAGLRenderContext);

ZGE_END_NAMESPACE
