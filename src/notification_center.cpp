/*
 * notification_center.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/29/2012
 */
 
#include "zge/notification_center.h"
#include "zge/logger.h"

namespace zge {

notification_center* notification_center::instance()
{
    static notification_center center;
    return &center;
}

uid notification_center::add_observer(std::string name, observer_function function)
{
    auto pair = std::make_pair(uid(), function);
    _observer_map[name].push_back(pair);
    return pair.first;
}

void notification_center::remove_observer(uid handle)
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
            logger::log("Warning (%s): Observer not found--could not remove.", __func__);
        }
    }
}

void notification_center::remove_observers(std::string name)
{
    _observer_map[name].clear();
}

void notification_center::post_notification(const notification &notification)
{
    if (_observer_map.count(notification.name)) {
        auto observers = _observer_map[notification.name];
        for (observer_pair &observer : observers) {
            observer.second(&notification);
        }
    }
}

void notification_center::post_notification(std::string name, void *sender)
{
    notification n;
    n.name = name;
    n.sender = sender;
    
    post_notification(n);
}

} // namespace zge
