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

ZEAGLRenderContext::ZEAGLRenderContext(ZEAGLRenderingAPI api)
{
    NSUInteger eagl_api = _eagl_api_from_zrendering_api(api);
    _eagl_context = [[EAGLContext alloc] initWithAPI:(EAGLRenderingAPI)eagl_api];
    initialize_shaders();
}

ZEAGLRenderContext::ZEAGLRenderContext(EAGLContext *context) :
    _eagl_context(context)
{
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

#pragma mark - Internal

unsigned ZEAGLRenderContext::_eagl_api_from_zrendering_api(ZEAGLRenderingAPI zapi)
{
    NSUInteger api = kEAGLRenderingAPIOpenGLES1;
    switch (zapi) {
        case ZEAGL_RENDERING_API_OPENGLES1:
            api = kEAGLRenderingAPIOpenGLES1;
            break;
        case ZEAGL_RENDERING_API_OPENGLES2:
            api = kEAGLRenderingAPIOpenGLES2;
            break;
        case ZEAGL_RENDERING_API_OPENGLES3:
            api = kEAGLRenderingAPIOpenGLES3;
            break;
        default:
            break;
    }
    return api;
}

ZGE_END_NAMESPACE
