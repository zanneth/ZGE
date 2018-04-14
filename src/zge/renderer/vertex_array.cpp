/*
 * vertex_array.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#include <zge/renderer/vertex_array.h>
#include <zge/util/glutil.h>
#include <zge/util/logger.h>
#include <zge/renderer/render_context.h>
#include <zge/util/util.h>
#include <set>

ZGE_BEGIN_NAMESPACE

ZVertexArray::ZVertexArray(uint32_t va_name, const std::function<void(uint32_t)> &deleter) :
    _vao(va_name),
    _deleter(deleter)
{}

ZVertexArray::~ZVertexArray()
{
    _deleter(_vao);
}

#pragma mark - API

void ZVertexArray::add_buffer(ZGraphicsBufferRef buffer, ZVertexAttributeIndex index)
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to add buffer for unknown attribute index %d", index);
    _buffers[index] = buffer;
}

void ZVertexArray::remove_buffer(ZVertexAttributeIndex index)
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to remove buffer for unknown attribute index %d", index);
    _buffers[index] = nullptr;
    _defined_attributes.erase(index);
}

void ZVertexArray::clear_buffers()
{
    for (unsigned i = 0; i < ZVERTEX_ATTRIB_COUNT; ++i) {
        _buffers[i] = nullptr;
    }
    _defined_attributes.clear();
}

uint32_t ZVertexArray::get_vao_name() const
{
    return _vao;
}

const ZGraphicsBufferRef& ZVertexArray::get_buffer(ZVertexAttributeIndex index) const
{
    zassert(index < ZVERTEX_ATTRIB_COUNT, "Attempted to access buffer at unknown attribute index %d", index);
    return _buffers[index];
}

const ZVertexBuffersArray& ZVertexArray::get_buffers() const
{
    return _buffers;
}

void ZVertexArray::set_element_buffer(ZElementGraphicsBufferRef element_buffer)
{
    _element_buffer = element_buffer;
}

const ZElementGraphicsBufferRef& ZVertexArray::get_element_buffer() const
{
    return _element_buffer;
}

ZGE_END_NAMESPACE
