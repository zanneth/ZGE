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
    static ZNotificationCenter center;
    return &center;
}

ZUID ZNotificationCenter::addObserver(std::string name, ZObserverFunction function)
{
    auto pair = std::make_pair(ZUID(), function);
    _observerMap[name].push_back(pair);
    return pair.first;
}

void ZNotificationCenter::removeObserver(ZUID handle)
{
    // OPTIMIZE: this could be improved
    for (auto &itm : _observerMap) {
        auto &observers = itm.second;
        auto result = std::find_if(observers.begin(), observers.end(), [&handle](const ZObserverPair &pair) -> bool {
            return pair.first == handle;
        });
        if (result != observers.end()) {
            observers.erase(result);
        } else {
            ZLogger::log("Warning (%s): Observer not found--could not remove.", __func__);
        }
    }
}

void ZNotificationCenter::removeObservers(std::string name)
{
    _observerMap[name].clear();
}

void ZNotificationCenter::postNotification(const ZNotification &notification)
{
    if (_observerMap.count(notification.name)) {
        auto observers = _observerMap[notification.name];
        for (ZObserverPair &observer : observers) {
            observer.second(&notification);
        }
    }
}

void ZNotificationCenter::postNotification(std::string name, void *sender)
{
    ZNotification n;
    n.name = name;
    n.sender = sender;
    
    postNotification(n);
}

} // namespace zge
