/*
 * schedulable.hpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 09/23/2014
 */

#include <zge/schedulable.h>

#ifndef __ZGE_ZSCHEDULABLE_IMPL_GUARD__
#error "Do not include this file directly. Include schedulable.h instead.
#endif

BEGIN_ZGE_NAMESPACE

template<typename T>
ZWeakSchedulable<T>::ZWeakSchedulable(std::weak_ptr<T> weak) :
    _ref(weak)
{}

template<typename T>
ZWeakSchedulable<T>::ZWeakSchedulable(std::shared_ptr<T> shared) :
    _ref(shared)
{}

template<typename T>
void ZWeakSchedulable<T>::run(uint32_t dtime)
{
    std::shared_ptr<T> shared = _ref.lock();
    if (shared) {
        shared->run();
    }
}

END_ZGE_NAMESPACE
