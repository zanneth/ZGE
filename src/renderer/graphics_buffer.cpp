/*
 * gl_buffer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */

#include <zge/graphics_buffer.h>
#include <zge/vertexarray.h>
#include <zge/exception.h>
#include <zge/logger.h>

namespace zge {

ZGraphicsBuffer::ZGraphicsBuffer() :
    _buffer(ZUNALLOCATED_BUFFER),
    _target(ZUNBOUND_TARGET),
    _vertex_array(nullptr)
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
    
#pragma mark - Attributes

void ZGraphicsBuffer::add_attribute(ZBufferAttribute attribute)
{
    _attributes.push_back(attribute);
    if (_vertex_array != nullptr) {
        _vertex_array->bind();
        _vertex_array->_enable_buffer_attribute(attribute);
        _send_attribute(attribute);
    }
}

ZBufferAttribute ZGraphicsBuffer::get_attribute(ZVertexAttributeIndex index)
{
    auto itr = std::find_if(_attributes.begin(), _attributes.end(), [index](ZBufferAttribute attrib) {
        return attrib.index == index;
    });
    
    if (itr == _attributes.end()) {
        ZException exception(ASSERTION_EXCEPTION_CODE);
        exception.description = "Could not find attribute for specified index.";
        throw exception;
    }
    
    return *itr;
}

void ZGraphicsBuffer::clear_attributes()
{
    if (_vertex_array != nullptr) {
        _vertex_array->bind();
        for (ZBufferAttribute attrib : _attributes) {
            _vertex_array->_disable_buffer_attribute(attrib);
        }
    }
    
    _attributes.clear();
}

#pragma mark - Loading Data

void ZGraphicsBuffer::load_data(GLsizeiptr size, const GLvoid *data, GLenum usage)
{
    _assert_target_bound();
    
    bind();
    glBufferData(_target, size, data, usage);
    if (_vertex_array == nullptr || !_vertex_array->is_bound()) {
        unbind();
    }
}

void ZGraphicsBuffer::load_subdata(GLsizeiptr offset, GLsizeiptr size, const GLvoid *data)
{
    _assert_target_bound();
    
    bind();
    glBufferSubData(_target, offset, size, data);
    if (_vertex_array == nullptr || !_vertex_array->is_bound()) {
        unbind();
    }
}

#pragma mark - Actions

void ZGraphicsBuffer::bind()
{
    if (_vertex_array != nullptr) {
        _vertex_array->bind();
    }
    
    glBindBuffer(_target, _buffer);
    for (const ZBufferAttribute &buffer_attribute : _attributes) {
        _send_attribute(buffer_attribute);
    }
}

void ZGraphicsBuffer::unbind()
{
    glBindBuffer(_target, 0);
}

#pragma mark - Private

void ZGraphicsBuffer::_move(ZGraphicsBuffer &&mv)
{
    _buffer = mv._buffer;
    _target = mv._target;
    _attributes = std::move(mv._attributes);
    _vertex_array = mv._vertex_array;
    
    mv._buffer = ZUNALLOCATED_BUFFER;
    mv._target = ZUNBOUND_TARGET;
    mv._vertex_array = nullptr;
}

void ZGraphicsBuffer::_assert_target_bound()
{
    if (_target == ZUNBOUND_TARGET) {
        ZException e(ENGINE_EXCEPTION_CODE);
        e.extra_info = "Attempted to load data into a buffer with no target buffer object.";
        throw e;
    }
}

void ZGraphicsBuffer::_send_attribute(const ZBufferAttribute &attribute)
{
    GLboolean normalized_val = attribute.normalized ? GL_TRUE : GL_FALSE;
    glBindBuffer(_target, _buffer);
    glVertexAttribPointer(attribute.index, attribute.components_per_vertex, attribute.component_type, normalized_val, attribute.stride, (const GLvoid *)attribute.offset);
}

} // namespace zge
