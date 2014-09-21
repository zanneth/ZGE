/*
 * camera.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 06/30/2012
 */
 
#pragma once

#include <zge/foundation.h>
#include <zge/render_context.h>

BEGIN_ZGE_NAMESPACE

class ZCamera : ZNoncopyable {
protected:
    ZRenderContextRef _current_context;
    
public:
    virtual ~ZCamera() = default;
    
    /* Open/Close */
    virtual void open(ZRenderContextRef context) = 0;
    virtual bool is_open() const = 0;
    virtual void close() = 0;
};

typedef std::shared_ptr<ZCamera> ZCameraRef;

END_ZGE_NAMESPACE
