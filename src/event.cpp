/*
 * event.cpp
 *
 * Author: Charles Magahern <charles@magahern.com>
 * Date Created: 10/29/2012
 */

#include "event.h"
#include "util.h"

namespace zge {

std::string _mouse_buttons_description(ZMouseButtonFlags button_flags);

std::string ZEvent::get_description()
{
    const char *format = "[ZEvent 0x%x] {\n"
        "\tTimestamp: %d\n"
        "\tType: %s\n"
        "\tContext: 0x%x\n"
        "\tIs Repeat: %s\n"
        "\tDetails:\n\t\t%s\n"
        "}"
    ;
    std::string type_str = _type_description();
    const char *is_repeat_str = is_repeat ? "true" : "false";
    
    std::string details_str;
    switch (type) {
        case MOUSE_DOWN_EVENT:
        case MOUSE_UP_EVENT:
        case MOUSE_MOVED_EVENT:
        case MOUSE_DRAGGED_EVENT:
        case SCROLL_WHEEL_EVENT:
            details_str = _mouse_event_description();
            break;
        case TOUCH_DOWN_EVENT:
        case TOUCH_UP_EVENT:
            details_str = _touch_event_description();
            break;
        case KEY_DOWN_EVENT:
        case KEY_UP_EVENT:
            details_str = _key_event_description();
            break;
        case APPLICATION_EVENT:
            details_str = _application_event_description();
            break;
        default:
            details_str = "N/A";
            break;
    }
    
    std::string description = util::format(format, this, timestamp, type_str.c_str(), &context, is_repeat_str, details_str.c_str());
    return description;
}

#pragma mark - Internal

std::string ZEvent::_type_description()
{
    std::string descr;
    switch (type) {
        case MOUSE_DOWN_EVENT:
            descr = "Mouse Down Event";
            break;
        case MOUSE_UP_EVENT:
            descr = "Mouse Up Event";
            break;
        case MOUSE_MOVED_EVENT:
            descr = "Mouse Moved Event";
            break;
        case MOUSE_DRAGGED_EVENT:
            descr = "Mouse Dragged Event";
            break;
        case SCROLL_WHEEL_EVENT:
            descr = "Scroll Wheel Event";
            break;
        case TOUCH_DOWN_EVENT:
            descr = "Touch Down Event";
            break;
        case TOUCH_UP_EVENT:
            descr = "Touch Up Event";
            break;
        case KEY_DOWN_EVENT:
            descr = "Key Down Event";
            break;
        case KEY_UP_EVENT:
            descr = "Key Up Event";
            break;
        case USER_EVENT:
            descr = "User Event";
            break;
        case APPLICATION_EVENT:
            descr = "Application Event";
            break;
        case SYSTEM_EVENT:
            descr = "System Event";
            break;
        case PERIODIC_EVENT:
            descr = "Periodic/Timer Event";
            break;
        case OTHER_EVENT:
        case UNKNOWN_EVENT:
        default:
            descr = "Unknown Event";
            break;
    }
    
    return descr;
}

std::string ZEvent::_key_event_description()
{
    std::string descr;
    ZKeyEvent key_event = event.key_event;
    
    descr = util::format("KeyCode: %d\n", key_event.key);
    
    unsigned modifier_flags = static_cast<unsigned>(key_event.modifier_flags);
    std::vector<std::string> modifier_strings;
    if (modifier_flags & LEFT_SHIFT_KEY) {
        modifier_strings.push_back("LSHIFT");
    }
    if (modifier_flags & RIGHT_SHIFT_KEY) {
        modifier_strings.push_back("RSHIFT");
    }
    if (modifier_flags & LEFT_CONTROL_KEY) {
        modifier_strings.push_back("LCONTROL");
    }
    if (modifier_flags & RIGHT_CONTROL_KEY) {
        modifier_strings.push_back("RCONTROL");
    }
    if (modifier_flags & LEFT_ALT_KEY) {
        modifier_strings.push_back("LALT");
    }
    if (modifier_flags & RIGHT_ALT_KEY) {
        modifier_strings.push_back("RALT");
    }
    if (modifier_flags & LEFT_META_KEY) {
        modifier_strings.push_back("LMETA");
    }
    if (modifier_flags & RIGHT_META_KEY) {
        modifier_strings.push_back("RMETA");
    }
    if (modifier_flags & NUM_LOCK_KEY) {
        modifier_strings.push_back("NUMLOCK");
    }
    if (modifier_flags & CAPS_LOCK_KEY) {
        modifier_strings.push_back("CAPSLOCK");
    }
    
    std::string modifiers_string;
    if (modifier_strings.size() > 0) {
        modifiers_string = util::separate_components(modifier_strings, ", ");
    } else {
        modifiers_string = "(no modifiers)\n";
    }
    descr += util::format("Modifier Keys: %s\n", modifiers_string.c_str());
    
    descr += util::format("Button State: %s", key_event.state == PRESSED ? "Pressed" : "Not Pressed");
    
    return descr;
}

std::string ZEvent::_mouse_event_description()
{
    std::string descr;
    ZMouseEvent mouse_event = event.mouse_event;
    descr = util::format("Location: (%f, %f)\n", mouse_event.location.x(), mouse_event.location.y());
    descr += util::format("Velocity: (%f, %f)\n", mouse_event.velocity.x(), mouse_event.velocity.y());
    
    std::string pressed_str = _mouse_buttons_description(mouse_event.pressed_buttons);
    std::string released_str = _mouse_buttons_description(mouse_event.released_buttons);
    descr += util::format("Pressed: %s\n", pressed_str.c_str());
    descr += util::format("Released: %s\n", released_str.c_str());
    
    descr += util::format("Click Count: %d", mouse_event.click_count);
    
    return descr;
}

std::string ZEvent::_touch_event_description()
{
    std::string descr;
    std::vector<ZTouchEvent> touch_events = event.touch_events;
    descr = util::format("Number of Touches: %d\n", touch_events.size());
    
    unsigned idx = 1;
    for (const auto &touch : touch_events) {
        descr += util::format("\tTouch %d:\n", idx);
        descr += util::format("\t\tLocation: (%f, %f)\n", touch.location.x(), touch.location.y());
        descr += util::format("\t\tTaps: %d\n", touch.tap_count);
        ++idx;
    }
    
    return descr;
}

std::string ZEvent::_application_event_description()
{
    std::string descr;
    ZApplicationEvent app_event = event.application_event;
    switch (app_event) {
        case APPLICATION_QUIT_EVENT:
            descr = "Application Quit Event";
            break;
        case APPLICATION_SUSPENDED_EVENT:
            descr = "Application Suspended Event";
            break;
        case APPLICATION_ACTIVE_EVENT:
            descr = "Application Active Event";
            break;
        case APPLICATION_INACTIVE_EVENT:
            descr = "Application Inactive Event";
            break;
        case UNKNOWN_APPLICATION_EVENT:
        default:
            descr = "Unknown Application Event";
            break;
    }
    
    return descr;
}

std::string _mouse_buttons_description(ZMouseButtonFlags button_flags)
{
    unsigned buttons = static_cast<unsigned>(button_flags);
    std::vector<std::string> button_strings;
    if (buttons & LEFT_MOUSE_BUTTON) {
        button_strings.push_back("LEFTBUTTON");
    }
    if (buttons & MIDDLE_MOUSE_BUTTON) {
        button_strings.push_back("MIDDLEBUTTON");
    }
    if (buttons & RIGHT_MOUSE_BUTTON) {
        button_strings.push_back("RIGHTBUTTON");
    }
    if (buttons & WHEEL_DOWN) {
        button_strings.push_back("WHEELDOWN");
    }
    if (buttons & WHEEL_UP) {
        button_strings.push_back("WHEELUP");
    }
    if (buttons & MOUSE_BUTTON_1) {
		button_strings.push_back("MOUSEBUTTON1");
	}
	if (buttons & MOUSE_BUTTON_2) {
		button_strings.push_back("MOUSEBUTTON2");
	}
	if (buttons & MOUSE_BUTTON_3) {
		button_strings.push_back("MOUSEBUTTON3");
	}
	if (buttons & MOUSE_BUTTON_4) {
		button_strings.push_back("MOUSEBUTTON4");
	}
	if (buttons & MOUSE_BUTTON_5) {
		button_strings.push_back("MOUSEBUTTON5");
	}
	if (buttons & MOUSE_BUTTON_6) {
		button_strings.push_back("MOUSEBUTTON6");
	}
	if (buttons & MOUSE_BUTTON_7) {
		button_strings.push_back("MOUSEBUTTON7");
	}
	if (buttons & MOUSE_BUTTON_8) {
		button_strings.push_back("MOUSEBUTTON8");
	}
    
    std::string buttons_string;
    if (button_strings.size() > 0) {
        buttons_string = util::separate_components(button_strings, ", ");
    } else {
        buttons_string = "(no buttons)";
    }
    
    return buttons_string;
}
    
} // namespace zge
