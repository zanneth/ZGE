/*
 * uniform.hpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/10/2014
 */

#include <algorithm>
#include <cstring>

BEGIN_ZGE_NAMESPACE

template <typename T, unsigned count>
ZUniform<T, count>::ZUniform(std::string name, GLint location, GLenum type) :
    ZUniformBase(name, location, type)
{
    bzero(_values, count * sizeof(T));
}
    
template <typename T, unsigned count>
ZUniform<T, count>::ZUniform(const ZUniform<T, count> &cp) :
    ZUniformBase(cp)
{
    for (unsigned i = 0; i < count; ++i) {
        _values[i] = cp._values[i];
    }
}

template <typename T, unsigned count>
ZUniform<T, count>::ZUniform(ZUniform<T, count> &&mv) :
    ZUniformBase(mv)
{
    _values = mv._values;
    mv._values = nullptr;
}

template <typename T, unsigned count>
ZUniform<T, count>::~ZUniform()
{}

#pragma mark - Accessors

template <typename T, unsigned count>
const void* ZUniform<T, count>::get_data(size_t *out_length) const
{
    if (out_length != nullptr) {
        *out_length = count * sizeof(T);
    }
    return _values;
}

template <typename T, unsigned count>
void ZUniform<T, count>::set_data(const void *data)
{
    memcpy(_values, data, count * sizeof(T));
    notify_observers(shared_from_this());
}

END_ZGE_NAMESPACE
