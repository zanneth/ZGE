/*
 * gl_vertexarray.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/18/2013
 */

#include <zge/vertexarray.h>
#include <zge/logger.h>

static GLuint __bound_vertex_array_object = 0;

namespace zge {

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
    unbind();
    
    if (_vertex_array_obj != ZUNALLOCATED_BUFFER) {
        glDeleteVertexArrays(1, &_vertex_array_obj);
        _vertex_array_obj = ZUNALLOCATED_BUFFER;
    }
    
    zlog("Vertex Array %p deleted.", this);
}

#pragma mark - API

void ZVertexArray::add_buffer(ZGraphicsBufferRef buffer)
{
    auto existing_itr = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (existing_itr == _buffers.end()) {
        bind();
        
        buffer->bind();
        buffer->_vertex_array = this;
        for (ZBufferAttribute buffer_attrib : buffer->get_attributes()) {
            _enable_buffer_attribute(buffer_attrib);
        }
        
        _buffers.push_back(buffer);
    } else {
        zlog("Vertex buffer object %p already bound.", buffer.get());
    }
}

void ZVertexArray::remove_buffer(ZGraphicsBufferRef buffer)
{
    auto itr = std::find(_buffers.begin(), _buffers.end(), buffer);
    if (itr != _buffers.end()) {
        bind();
        
        buffer->unbind();
        buffer->_vertex_array = nullptr;
        for (ZBufferAttribute buffer_attrib : buffer->get_attributes()) {
            _disable_buffer_attribute(buffer_attrib);
        }
        
        _buffers.erase(itr);
    } else {
        zlog("Vertex buffer object %p cannot be removed from vertex array. Not found in buffers list.", buffer.get());
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

void ZVertexArray::bind()
{
    if (!is_bound()) {
        glBindVertexArray(_vertex_array_obj);
        __bound_vertex_array_object = _vertex_array_obj;
    }
}

void ZVertexArray::unbind()
{
    if (is_bound()) {
        glBindVertexArray(0);
        __bound_vertex_array_object = 0;
    }
}

bool ZVertexArray::is_bound()
{
    return (__bound_vertex_array_object == _vertex_array_obj);
}

#pragma mark - Private

void ZVertexArray::_enable_buffer_attribute(const ZBufferAttribute &attribute)
{
    glEnableVertexAttribArray(attribute.index);
}

void ZVertexArray::_disable_buffer_attribute(const ZBufferAttribute &attribute)
{
    glDisableVertexAttribArray(attribute.index);
}

} // namespace zge
