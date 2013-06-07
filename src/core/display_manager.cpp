/*
 * display_manager.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 02/03/2012
 */
 
#include <zge/display_manager.h>
#include <zge/display.h>
#include <zge/exception.h>
#include <zge/notification_center.h>

namespace zge {

const std::string ZDisplayManagerDidCreateDisplayNotification = "ZDisplayManagerDidCreateDisplayNotification";

ZDisplayManager::ZDisplayManager() :
    _current_display(nullptr)
{}

ZDisplayManager::~ZDisplayManager()
{}

ZDisplayRef ZDisplayManager::create_display(const ZDisplayMode &mode)
{
    ZDisplayRef display = ZDisplayRef(new ZDisplay(mode));
    display->initialize();
    
    _current_display = display;
    
    ZNotification notification;
    notification.name = ZDisplayManagerDidCreateDisplayNotification;
    notification.sender = this;
    ZNotificationCenter::instance()->post_notification(notification);
    
    return _current_display;
}

void ZDisplayManager::run(uint32_t dtime)
{
    if (_current_display != nullptr) {
        if (!_current_display->is_initialized()) {
            _current_display->initialize();
        }
        
        _current_display->update(dtime);
    }
}

} // namespace zge
