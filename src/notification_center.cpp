/*
 * notification_center.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/29/2012
 */
 
#include "zge/notification_center.h"
#include "zge/logger.h"

namespace zge {

ZNotificationCenter* ZNotificationCenter::instance()
{
    static ZNotificationCenter __center;
    return &__center;
}

ZUID ZNotificationCenter::add_observer(std::string name, ZObserverFunction function)
{
    auto pair = std::make_pair(ZUID(), function);
    _observer_map[name].push_back(pair);
    return pair.first;
}

void ZNotificationCenter::remove_observer(ZUID handle)
{
    for (auto &itm : _observer_map) {
        auto &observers = itm.second;
        auto result = std::find_if(observers.begin(),
                                   observers.end(),
                                   [&handle](const observer_pair &pair) -> bool {
            return pair.first == handle;
        });
        if (result != observers.end()) {
            observers.erase(result);
        } else {
            ZLogger::log("Warning (%s): Observer not found--could not remove.", __func__);
        }
    }
}

void ZNotificationCenter::remove_observers(std::string name)
{
    _observer_map[name].clear();
}

void ZNotificationCenter::post_notification(const ZNotification &notification)
{
    if (_observer_map.count(notification.name)) {
        auto observers = _observer_map[notification.name];
        for (observer_pair &observer : observers) {
            observer.second(&notification);
        }
    }
}

void ZNotificationCenter::post_notification(std::string name, void *sender)
{
    ZNotification n;
    n.name = name;
    n.sender = sender;
    
    post_notification(n);
}

} // namespace zge
