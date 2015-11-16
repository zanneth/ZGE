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
#include <zge/opengl.h>

ZGE_BEGIN_NAMESPACE

ZGraphicsBuffer::ZGraphicsBuffer(uint32_t buffer_name, ZBufferTarget target, const std::function<void(uint32_t)> &deleter) :
    _buffer(buffer_name),
    _target(target),
    _deleter(deleter)
{}

ZGraphicsBuffer::~ZGraphicsBuffer()
{
    _deleter(_buffer);
}

#pragma mark - Accessors

uint32_t ZGraphicsBuffer::get_name() const { return _buffer; }

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

void ZGraphicsBuffer::load_data(const ZData &data, ZBufferUsage usage)
{
    _pending_buffer.data = data;
    _pending_buffer.usage = usage;
}

void ZGraphicsBuffer::load_data(const void *bytes, size_t length, ZBufferUsage usage)
{
    _pending_buffer.data = ZData(bytes, length);
    _pending_buffer.usage = usage;
}

const ZPendingGraphicsBuffer& ZGraphicsBuffer::get_pending_buffer() const
{
    return _pending_buffer;
}

void ZGraphicsBuffer::clear_pending_buffer()
{
    _pending_buffer = ZPendingGraphicsBuffer();
}

#pragma mark - ZElementGraphicsBuffer

ZElementGraphicsBuffer::ZElementGraphicsBuffer(uint32_t buffer_name, const std::function<void(uint32_t)> &deleter) :
    ZGraphicsBuffer(buffer_name, ZBUFFER_TARGET_ELEMENT_ARRAY, deleter),
    _elements_count(0),
    _indices_type(ZCOMPONENT_TYPE_UNSIGNED_INT)
{}

void ZElementGraphicsBuffer::set_elements_count(unsigned count) { _elements_count = count; }

unsigned ZElementGraphicsBuffer::get_elements_count() const { return _elements_count; }

void ZElementGraphicsBuffer::set_indices_type(ZComponentType type) { _indices_type = type; }

ZComponentType ZElementGraphicsBuffer::get_indices_type() const { return _indices_type; }

ZGE_END_NAMESPACE
