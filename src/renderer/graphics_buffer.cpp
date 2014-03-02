/*
 * gl_buffer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */

#include <zge/graphics_buffer.h>
#include <zge/glutil.h>
#include <zge/vertexarray.h>
#include <zge/exception.h>
#include <zge/logger.h>

BEGIN_ZGE_NAMESPACE

ZGraphicsBuffer::ZGraphicsBuffer() :
    _buffer(ZUNALLOCATED_BUFFER),
    _target(ZBUFFER_TARGET_ARRAY)
{
    glGenBuffers(1, &_buffer);
}

ZGraphicsBuffer::ZGraphicsBuffer(ZGraphicsBuffer &&mv)
{
    _move(std::move(mv));
}

ZGraphicsBuffer& ZGraphicsBuffer::operator=(ZGraphicsBuffer &&mv)
{
    _move(std::move(mv));
    return *this;
}

ZGraphicsBuffer::~ZGraphicsBuffer()
{
    if (_buffer != ZUNALLOCATED_BUFFER) {
        glDeleteBuffers(1, &_buffer);
    }
    zlog("Buffer %p deleted.", this);
}

#pragma mark - Accessors

ZBufferTarget ZGraphicsBuffer::get_target() { return _target; }

void ZGraphicsBuffer::set_target(ZBufferTarget target)
{
    _unbind();
    _target = target;
}

#pragma mark - Attributes

void ZGraphicsBuffer::add_attribute(ZBufferAttribute attribute)
{
    _attributes.push_back(attribute);
    
    // clear bound vertex array to reload attributes
    _bound_vertex_array.reset();
}

ZBufferAttribute ZGraphicsBuffer::get_attribute(ZVertexAttributeIndex index)
{
    auto itr = std::find_if(_attributes.begin(), _attributes.end(), [index](ZBufferAttribute attrib) {
        return attrib.index == index;
    });
    
    if (itr == _attributes.end()) {
        ZException exception(ZASSERTION_EXCEPTION_CODE);
        exception.description = "Could not find attribute for specified index.";
        throw exception;
    }
    
    return *itr;
}

void ZGraphicsBuffer::clear_attributes()
{
    _attributes.clear();
    _bound_vertex_array.reset();
}

#pragma mark - Loading Data

void ZGraphicsBuffer::load_data(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    _assert_target_bound();
    _bind();
    
    glBufferData(_target, size, data, usage);
    
    if (_bound_vertex_array.expired()) {
        _unbind();
    }
}

void ZGraphicsBuffer::load_subdata(GLsizeiptr offset, GLsizeiptr size, const GLvoid *data)
{
    _assert_target_bound();
    _bind();
    
    glBufferSubData(_target, offset, size, data);
    
    if (_bound_vertex_array.expired()) {
        _unbind();
    }
}

#pragma mark - Private

void ZGraphicsBuffer::_bind()
{
    glBindBuffer(_target, _buffer);
    for (const ZBufferAttribute &buffer_attribute : _attributes) {
        _send_attribute(buffer_attribute);
    }
}

void ZGraphicsBuffer::_unbind()
{
    glBindBuffer(_target, 0);
}

void ZGraphicsBuffer::_move(ZGraphicsBuffer &&mv)
{
    _buffer = mv._buffer;
    _target = mv._target;
    _attributes = std::move(mv._attributes);
    _bound_vertex_array = mv._bound_vertex_array;
    
    mv._buffer = ZUNALLOCATED_BUFFER;
    mv._target = (ZBufferTarget)ZUNBOUND_TARGET;
    mv._bound_vertex_array.reset();
}

void ZGraphicsBuffer::_assert_target_bound()
{
    if (_target == ZUNBOUND_TARGET) {
        ZException e(ZENGINE_EXCEPTION_CODE);
        e.extra_info = "Attempted to load data into a buffer with no target buffer object.";
        throw e;
    }
}

void ZGraphicsBuffer::_send_attribute(const ZBufferAttribute &attribute)
{
    GLboolean normalized_val = attribute.normalized ? GL_TRUE : GL_FALSE;
    GLenum value_type = ZGLUtil::gl_value_type_from_component_type(attribute.component_type);
    glBindBuffer(_target, _buffer);
    glVertexAttribPointer(attribute.index, attribute.components_per_vertex, value_type, normalized_val, attribute.stride, (const GLvoid *)attribute.offset);
}

END_ZGE_NAMESPACE
