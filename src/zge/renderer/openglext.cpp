//
//  openglext.cpp
//  ZGE
//
//  Created by Charles Magahern on 10/16/16.
//  Copyright © 2016 omegaHern. All rights reserved.
//

#include "openglext.h"

ZGE_BEGIN_NAMESPACE

ZOpenGLExtensions::ZOpenGLExtensions() :
    _varray_bind(nullptr),
    _varray_delete(nullptr),
    _varray_gen(nullptr),
    _varray_is_varray(nullptr)
{
#if OPENGL_ES2
    _varray_bind = (ZOGLBindVArrayFunctionPtr)eglGetProcAddress("glBindVertexArrayOES");
    _varray_delete = (ZOGLDeleteVArrayFunctionPtr)eglGetProcAddress("glDeleteVertexArraysOES");
    _varray_gen = (ZOGLGenVArrayFunctionPtr)eglGetProcAddress("glGenVertexArraysOES");
    _varray_is_varray = (ZOGLIsVArrayFunctionPtr)eglGetProcAddress("glIsVertexArrayOES");
#else
    _varray_bind = glBindVertexArray;
    _varray_delete = glDeleteVertexArrays;
    _varray_gen = glGenVertexArrays;
    _varray_is_varray = glIsVertexArray;
#endif
}

ZOGLBindVArrayFunctionPtr ZOpenGLExtensions::get_varray_bind_function() const { return _varray_bind; }
ZOGLDeleteVArrayFunctionPtr ZOpenGLExtensions::get_varray_delete_function() const { return _varray_delete; }
ZOGLGenVArrayFunctionPtr ZOpenGLExtensions::get_varray_gen_function() const { return _varray_gen; }
ZOGLIsVArrayFunctionPtr ZOpenGLExtensions::get_varray_is_varray_function() const { return _varray_is_varray; }

ZGE_END_NAMESPACE
