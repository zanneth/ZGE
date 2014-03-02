/*
 * gl_vertexarray.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#include <zge/vertexarray.h>
#include <zge/logger.h>

BEGIN_ZGE_NAMESPACE

ZVertexArray::ZVertexArray(std::initializer_list<ZGraphicsBufferRef> buffers) :
    _vertex_array_obj(ZUNALLOCATED_BUFFER)
{
    glGenVertexArrays(1, &_vertex_array_obj);
    
    for (ZGraphicsBufferRef buffer : buffers) {
        add_buffer(buffer);
    }
}

ZVertexArray::ZVertexArray(ZVertexArray &&mv)
{
    mv._vertex_array_obj = _vertex_array_obj;
    _vertex_array_obj = ZUNALLOCATED_BUFFER;
}

ZVertexArray& ZVertexArray::operator=(ZVertexArray &&mv)
{
    _vertex_array_obj = mv._vertex_array_obj;
    mv._vertex_array_obj = ZUNALLOCATED_BUFFER;
    return *this;
}

ZVertexArray::~ZVertexArray()
{
    remove_all_buffers();
    
    if (_vertex_array_obj != ZUNALLOCATED_BUFFER) {
        glDeleteVertexArrays(1, &_vertex_array_obj);
        _vertex_array_obj = ZUNALLOCATED_BUFFER;
    }
}

#pragma mark - API

void ZVertexArray::add_buffer(ZGraphicsBufferRef buffer)
{
    auto existing_itr = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (existing_itr == _buffers.end()) {
        _buffers.push_back(buffer);
    }
}

void ZVertexArray::remove_buffer(ZGraphicsBufferRef buffer)
{
    auto itr = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (itr != _buffers.end()) {
        _buffers.erase(itr);
    }
}

void ZVertexArray::remove_all_buffers()
{
    std::vector<ZGraphicsBufferRef> buffers_to_remove = _buffers;
    for (ZGraphicsBufferRef buffer : buffers_to_remove) {
        remove_buffer(buffer);
    }
}

std::vector<ZGraphicsBufferRef> ZVertexArray::get_buffers()
{
    return _buffers;
}

#pragma mark - Private

void ZVertexArray::_bind()
{
    if (_vertex_array_obj) {
        glBindVertexArray(_vertex_array_obj);
    }
}

void ZVertexArray::_unbind()
{
    glBindVertexArray(0);
}

END_ZGE_NAMESPACE
