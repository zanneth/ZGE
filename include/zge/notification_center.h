/*
 * notification_center.h
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 08/29/2012
 */

#pragma once

#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "zge/noncopyable.h"
#include "zge/types.h"

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

class ZNotificationCenter : ZNoncopyable {
    typedef std::pair<ZUID, ZObserverFunction> observer_pair;
    std::map<std::string, std::vector<observer_pair>> _observer_map;

public:
    static ZNotificationCenter* instance();

    ZUID add_observer(std::string name, ZObserverFunction function);
    void remove_observer(ZUID handle);
    void remove_observers(std::string name);
    
    void post_notification(const ZNotification &notification);
    void post_notification(std::string name, void *sender = nullptr);

private:
    // singleton
    ZNotificationCenter() = default;
};

} // namespace zge
