/*
 * gl_buffer.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/29/2012
 */

#include <zge/graphics_buffer.h>
#include <zge/glutil.h>
#include <zge/exception.h>
#include <zge/logger.h>

BEGIN_ZGE_NAMESPACE

ZGraphicsBuffer::ZGraphicsBuffer(ZBufferTarget target) :
    _buffer(ZUNALLOCATED_BUFFER),
    _target(target)
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

ZBufferTarget ZGraphicsBuffer::get_target() const { return _target; }

#pragma mark - Attributes

void ZGraphicsBuffer::add_attribute(ZBufferAttribute attribute)
{
    _attributes.push_back(attribute);
}

std::vector<ZBufferAttribute> ZGraphicsBuffer::get_attributes() const
{
    return _attributes;
}

void ZGraphicsBuffer::clear_attributes()
{
    _attributes.clear();
}

#pragma mark - Loading Data

void ZGraphicsBuffer::load_data(const void *data, size_t length, ZBufferUsage usage)
{
    _bind();
    
    GLenum target = ZGLUtil::gl_target_from_buffer_target(_target);
    GLenum glusage = ZGLUtil::gl_usage_from_buffer_usage(usage);
    glBufferData(target, (GLsizeiptr)length, (const GLvoid *)data, glusage);
}

#pragma mark - Private

void ZGraphicsBuffer::_bind()
{
    GLenum target = ZGLUtil::gl_target_from_buffer_target(_target);
    glBindBuffer(target, _buffer);
}

void ZGraphicsBuffer::_unbind()
{
    GLenum target = ZGLUtil::gl_target_from_buffer_target(_target);
    glBindBuffer(target, 0);
}

void ZGraphicsBuffer::_move(ZGraphicsBuffer &&mv)
{
    _buffer = mv._buffer;
    _target = mv._target;
    _attributes = std::move(mv._attributes);
    
    mv._buffer = ZUNALLOCATED_BUFFER;
    mv._target = (ZBufferTarget)ZUNBOUND_TARGET;
}

#pragma mark - ZElementGraphicsBuffer

ZElementGraphicsBuffer::ZElementGraphicsBuffer() : ZGraphicsBuffer(ZBUFFER_TARGET_ELEMENT_ARRAY),
    _elements_count(0),
    _indices_type(ZCOMPONENT_TYPE_UNSIGNED_INT)
{}

void ZElementGraphicsBuffer::set_elements_count(unsigned count) { _elements_count = count; }

unsigned ZElementGraphicsBuffer::get_elements_count() const { return _elements_count; }

void ZElementGraphicsBuffer::set_indices_type(ZComponentType type) { _indices_type = type; }

ZComponentType ZElementGraphicsBuffer::get_indices_type() const { return _indices_type; }

END_ZGE_NAMESPACE
