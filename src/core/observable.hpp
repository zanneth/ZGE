/*
 * observable.hpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 01/21/2014
 */

BEGIN_ZGE_NAMESPACE

template <typename T>
struct _ZObserver {
    uint32_t uid;
    ZObserverFunc<T> func;
};
template <typename T>
using ZObserverRef = std::shared_ptr<_ZObserver<T>>;

template <typename T>
struct ZObservableImpl {
    std::vector<ZObserverRef<T>> observers;
};

template <typename T>
ZObservable<T>::ZObservable() :
    _impl(new ZObservableImpl<T>)
{}

template <typename T>
ZObserver* ZObservable<T>::add_observer(ZObserverFunc<T> observer_func)
{
    ZObserverRef<T> observer = ZObserverRef<T>(new _ZObserver<T>({
        .uid = arc4random(),
        .func = observer_func
    }));
    _impl->observers.push_back(observer);
    return observer.get();
}

template <typename T>
void ZObservable<T>::remove_observer(ZObserver *observer)
{
    _ZObserver<T> *observer_ptr = static_cast<_ZObserver<T> *>(observer);
    uint32_t uid = observer_ptr->uid;
    auto itr = std::find_if(_impl->observers.begin(), _impl->observers.end(), [uid](ZObserverRef<T> other) -> bool {
        return other->uid == uid;
    });
    if (itr != _impl->observers.end()) {
        _impl->observers.erase(itr);
    }
}

template <typename T>
void ZObservable<T>::remove_all_observers()
{
    _impl->observers.clear();
}

template <typename T>
void ZObservable<T>::notify_observers(T object)
{
    for (auto &observer : _impl->observers) {
        observer->func(object);
    }
}

END_ZGE_NAMESPACE
