/*
 * vertex_array.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#include <zge/vertex_array.h>
#include <zge/glutil.h>
#include <zge/logger.h>
#include <zge/opengl.h>
#include <zge/render_context.h>
#include <zge/util.h>
#include <set>

BEGIN_ZGE_NAMESPACE

struct ZVertexArrayImpl {
    GLuint vao;
    ZElementGraphicsBufferRef element_buffer;
    std::array<ZGraphicsBufferRef, ZVERTEX_ATTRIB_COUNT> buffers;
    std::set<ZVertexAttributeIndex> defined_attributes;
};

static void _zvertexarray_setup_vertex_attrib_pointer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index);

#pragma mark -

ZVertexArray::ZVertexArray() :
    _impl(new ZVertexArrayImpl)
{
    glGenVertexArrays(1, &(_impl->vao));
}

ZVertexArray::~ZVertexArray()
{
    glDeleteVertexArrays(1, &(_impl->vao));
}

#pragma mark - API

void ZVertexArray::add_buffer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index)
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to add buffer for unknown attribute index %zd", index);
    _impl->buffers[index] = buffer;
}

void ZVertexArray::remove_buffer(ZVertexAttributeIndex index)
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to remove buffer for unknown attribute index %zd", index);
    _impl->buffers[index] = nullptr;
    _impl->defined_attributes.erase(index);
}

void ZVertexArray::clear_buffers()
{
    for (unsigned i = 0; i < ZVERTEX_ATTRIB_COUNT; ++i) {
        _impl->buffers[i] = nullptr;
    }
    _impl->defined_attributes.clear();
}

ZGraphicsBufferRef ZVertexArray::get_buffer(ZVertexAttributeIndex index) const
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to access buffer at unknown attribute index %zd", index);
    return _impl->buffers[index];
}

std::array<ZGraphicsBufferRef, ZVERTEX_ATTRIB_COUNT> ZVertexArray::get_buffers() const
{
    return _impl->buffers;
}

void ZVertexArray::set_element_buffer(ZElementGraphicsBufferRef element_buffer) { _impl->element_buffer = element_buffer; }

ZElementGraphicsBufferRef ZVertexArray::get_element_buffer() const { return _impl->element_buffer; }

#pragma mark - Private

void ZVertexArray::_bind(ZRenderContextRef context)
{
    glBindVertexArray(_impl->vao);
    
    for (unsigned i = 0; i < ZVERTEX_ATTRIB_COUNT; ++i) {
        ZVertexAttributeIndex index = (ZVertexAttributeIndex)i;
        ZGraphicsBufferRef buffer = _impl->buffers[index];
        if (buffer.get()) {
            buffer->_bind();
            if (_impl->defined_attributes.count(index) == 0) {
                _zvertexarray_setup_vertex_attrib_pointer(buffer, index);
                _impl->defined_attributes.insert(index);
            }
        }
    }
    
    if (_impl->element_buffer.get()) {
        _impl->element_buffer->_bind();
    }
    
    context->_bound_vertex_array = shared_from_this();
}

void ZVertexArray::_unbind(ZRenderContextRef context)
{
    ZVertexArrayRef bound_varray = context->_bound_vertex_array;
    if (bound_varray.get() == this) {
        glBindVertexArray(0);
        context->_bound_vertex_array = nullptr;
    } else {
        ZLogger::log_error("Attempted to unbind vertex array (%p) that is different from the one that is bound (%p)", this, bound_varray.get());
    }
}

#pragma mark - Internal

void _zvertexarray_setup_vertex_attrib_pointer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index)
{
    glEnableVertexAttribArray(index);
    
    std::vector<ZBufferAttribute> attributes = buffer->get_attributes();
    for (const ZBufferAttribute &attribute : attributes) {
        GLboolean normalized_val = attribute.normalized ? GL_TRUE : GL_FALSE;
        GLenum value_type = ZGLUtil::gl_value_type_from_component_type(attribute.component_type);
        glVertexAttribPointer(index, attribute.components_per_vertex, value_type, normalized_val, attribute.stride, (const GLvoid *)attribute.offset);
    }
}

END_ZGE_NAMESPACE
