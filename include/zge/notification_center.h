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
    
    std::string getDescription() const
    {
        std::ostringstream oss;
        oss << "ZNotification(0x" << this << ") { "
            "name: \"" << name << "\", "
            "sender: " << sender << ", "
            "info: " << &info << " }";
        return oss.str();
    }
};

typedef std::function<void(const ZNotification*)> ZObserverFunction;

class ZNotificationCenter : ZNonCopyable {
    typedef std::pair<ZUID, ZObserverFunction> ZObserverPair;
    std::map<std::string, std::vector<ZObserverPair>> _observerMap;

public:
    static ZNotificationCenter* instance();

    ZUID addObserver(std::string name, ZObserverFunction function);
    void removeObserver(ZUID handle);
    void removeObservers(std::string name);
    
    void postNotification(const ZNotification &notification);
    void postNotification(std::string name, void *sender = nullptr);

private:
    // singleton
    ZNotificationCenter() = default;
};

} // namespace zge
