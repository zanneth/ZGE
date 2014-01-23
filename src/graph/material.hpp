/*
 * material.hpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/22/2014
 */

namespace zge {

template <typename T>
ZMaterialProperty<T>::ZMaterialProperty(std::string name) :
    _name(name),
    _dirty(true)
{}

template <typename T>
T ZMaterialProperty<T>::get_contents() const { return _contents; }

template <typename T>
void ZMaterialProperty<T>::set_contents(const T &contents) { _contents = contents; _dirty = true; }

template <typename T>
std::string ZMaterialProperty<T>::get_name() const { return _name; }

template <typename T>
bool ZMaterialProperty<T>::is_dirty() const { return _dirty; }

template <typename T>
void ZMaterialProperty<T>::clear_dirty() { _dirty = false; }

} // namespace zge
