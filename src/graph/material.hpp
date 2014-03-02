/*
 * material.hpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/22/2014
 */

BEGIN_ZGE_NAMESPACE

template <typename T>
ZMaterialProperty<T>::ZMaterialProperty(std::string name) :
    _name(name)
{}

template <typename T>
ZMaterialProperty<T>::ZMaterialProperty(const ZMaterialProperty<T> &cp) :
    _contents(cp._contents),
    _name(cp._name)
{}

template <typename T>
ZMaterialProperty<T>::ZMaterialProperty(ZMaterialProperty<T> &&mv) :
    _contents(std::move(mv._contents)),
    _name(std::move(mv._name))
{}

template <typename T>
ZMaterialProperty<T>::~ZMaterialProperty()
{}

template <typename T>
T ZMaterialProperty<T>::get_contents() const { return _contents; }

template <typename T>
void ZMaterialProperty<T>::set_contents(const T &contents) { _contents = contents; }

template <typename T>
std::string ZMaterialProperty<T>::get_name() const { return _name; }

END_ZGE_NAMESPACE
