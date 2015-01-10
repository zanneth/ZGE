/*
 * eagl_render_context.mm
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/06/2015
 */

#include <zge/eagl_render_context.h>
#include <Eigen/Core> // must include Eigen headers first as this conflicts with ObjC runtime headers
#include <OpenGLES/EAGL.h>

ZGE_BEGIN_NAMESPACE

ZEAGLRenderContext::ZEAGLRenderContext()
{
    _eagl_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES3];
    initialize_shaders();
}

ZEAGLRenderContext::~ZEAGLRenderContext()
{
    if ([EAGLContext currentContext] == _eagl_context) {
        [EAGLContext setCurrentContext:nil];
    }
}

EAGLContext* ZEAGLRenderContext::get_eagl_context() const
{
    return _eagl_context;
}

void ZEAGLRenderContext::make_current()
{
    [EAGLContext setCurrentContext:_eagl_context];
}

ZGE_END_NAMESPACE
