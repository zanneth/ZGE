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

ZUUID ZNotificationCenter::addObserver(std::string name, ZObserverFunction function)
{
    _ZObserver obs;
    obs.function = function;
    _observerMap[name].push_back(obs);
    
    std::cout << obs.handle.getDescription() << std::endl;
    return obs.handle;
}

void ZNotificationCenter::removeObserver(ZUUID handle)
{
    // OPTIMIZE: this could be improved
    for (auto &itm : _observerMap) {
        auto &observers = itm.second;
        auto result = std::find_if(observers.begin(), observers.end(), [handle](const _ZObserver &observer) -> bool {
            return observer.handle == handle;
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
        for (_ZObserver &observer : observers) {
            observer.function(&notification);
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
