/*
 * notification_center.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/29/2012
 */

#pragma once

#include <functional>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "zge/noncopyable.h"

namespace zge {

struct ZNotification {
    std::string name;
    void *sender;   // weak
    void *info;     // weak
    
    std::string get_description() const
    {
        std::ostringstream oss;
        oss << "notification(0x" << this << ") { "
            "name: \"" << name << "\", "
            "sender: " << sender << ", "
            "info: " << &info << " }";
        return oss.str();
    }
};

typedef std::function<void(const ZNotification*)> ZObserverFunction;
typedef unsigned ZObserverHandle;

class ZNotificationCenter : ZNoncopyable {
    typedef std::pair<ZObserverHandle, ZObserverFunction> observer_pair;
    std::map<std::string, std::vector<observer_pair>> _observer_map;

public:
    static ZNotificationCenter* instance();

    ZObserverHandle add_observer(std::string name, ZObserverFunction function);
    void remove_observer(ZObserverHandle handle);
    void remove_observers(std::string name);
    
    void post_notification(const ZNotification &notification);
    void post_notification(std::string name, void *sender = nullptr);

private:
    // singleton
    ZNotificationCenter() = default;
};

} // namespace zge
