/*
 * observable.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/21/2014
 */

#pragma once

#include <iostream>
#include <functional>
#include <memory>
#include <vector>
#include <zge/core/defines.h>

ZGE_BEGIN_NAMESPACE
    
template <typename T> using ZObserverFunc = std::function<void(T)>;
template <typename T> struct ZObservableImpl;
typedef void ZObserver;
    
template <typename T>
class ZObservable {
public:
    ZObservable();
    
    ZObserver* add_observer(std::function<void(T)> observer_func);
    void remove_observer(ZObserver *observer);
    void remove_all_observers();
    
    void notify_observers(T object);
    
private:
    std::auto_ptr<ZObservableImpl<T>> _impl;
};

ZGE_END_NAMESPACE

#include <zge/core/observable.hpp>
