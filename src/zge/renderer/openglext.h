//
//  openglext.h
//  ZGE
//
//  Created by Charles Magahern on 10/16/16.
//  Copyright © 2016 omegaHern. All rights reserved.
//

#pragma once

#include <zge/core/foundation.h>
#include <zge/core/noncopyable.h>
#include <zge/renderer/opengl.h>

ZGE_BEGIN_NAMESPACE

using ZOGLBindVArrayFunctionPtr = void(*)(GLuint);
using ZOGLDeleteVArrayFunctionPtr = void(*)(GLsizei, const GLuint *);
using ZOGLGenVArrayFunctionPtr = void(*)(GLsizei, GLuint *);
using ZOGLIsVArrayFunctionPtr = GLboolean(*)(GLuint);

class ZOpenGLExtensions : ZNoncopyable {
public:
    ZOpenGLExtensions();
    virtual ~ZOpenGLExtensions() = default;
    
    ZGE_DEFINE_SREF_FUNCTIONS(ZOpenGLExtensions);
    
    ZOGLBindVArrayFunctionPtr get_varray_bind_function() const;
    ZOGLDeleteVArrayFunctionPtr get_varray_delete_function() const;
    ZOGLGenVArrayFunctionPtr get_varray_gen_function() const;
    ZOGLIsVArrayFunctionPtr get_varray_is_varray_function() const;
    
private:
    ZOGLBindVArrayFunctionPtr   _varray_bind;
    ZOGLDeleteVArrayFunctionPtr _varray_delete;
    ZOGLGenVArrayFunctionPtr    _varray_gen;
    ZOGLIsVArrayFunctionPtr     _varray_is_varray;
};

ZGE_DEFINE_SREF_TYPE(ZOpenGLExtensions);

ZGE_END_NAMESPACE
